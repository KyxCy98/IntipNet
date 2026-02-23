#!/usr/bin/env python3
import argparse
import json
import time
from urllib.parse import urlparse
import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry

BASE_CDX = "https://web.archive.org/cdx/search/cdx"

def build_session(retries, backoff_factor, status_forcelist=(429, 500, 502, 503, 504)):
    session = requests.Session()
    retry = Retry(
        total=retries,
        backoff_factor=backoff_factor,
        status_forcelist=list(status_forcelist),
        allowed_methods=["GET", "HEAD"],
        raise_on_status=False,
    )
    adapter = HTTPAdapter(max_retries=retry)
    session.mount("https://", adapter)
    session.mount("http://", adapter)
    session.headers.update({
        "User-Agent": "IntipNet-wayback/1.0 (+https://example.local)",
        "Accept": "application/json, text/plain, */*"
    })
    return session

def get_wayback_urls(session, domain, timeout):
    query = f"{domain}/*"
    params = {
        "url": query,
        "output": "json",
        "fl": "original",
        "collapse": "urlkey"
    }

    try:
        resp = session.get(BASE_CDX, params=params, timeout=timeout)
    except requests.exceptions.RequestException as e:
        print(f"[module] [error] Request error: {e}")
        return []

    if resp.status_code != 200:
        print(f"[module] [error] HTTP {resp.status_code} from Wayback API")
        return []

    text = resp.text.strip()
    if not text:
        print("[module] [warning] Empty response body")
        return []

    try:
        data = resp.json()
        if isinstance(data, list) and len(data) > 1:
            urls = [row[0] for row in data[1:] if row]
            return sorted(set(urls))
        elif isinstance(data, list) and len(data) == 1:
            return []
    except ValueError:
        urls = []
        for line in text.splitlines():
            line = line.strip()
            if not line:
                continue
            if line.startswith('['):
                try:
                    parsed = json.loads(line)
                    if isinstance(parsed, list):
                        for item in parsed:
                            if isinstance(item, str) and item.startswith("http"):
                                urls.append(item)
                except Exception:
                    pass
            elif line.startswith("http"):
                urls.append(line)
        return sorted(set(urls))

    return []

def save_output(domain, urls, outpath=None):
    filename = outpath or f"wayback-{domain}.txt"
    with open(filename, "w", encoding="utf-8") as f:
        for u in urls:
            f.write(u + "\n")
    print(f"[module] [info] Saved {len(urls)} url to {filename}")

def main():
    parser = argparse.ArgumentParser(description="Wayback URL Fetcher (robust)")
    parser.add_argument("-u", "--url", required=True, help="Target domain (example: example.com)")
    parser.add_argument("-o", "--output", action="store_true", help="Save result to file (wayback-<domain>.txt)")
    parser.add_argument("--outpath", help="Custom output file path")
    parser.add_argument("--timeout", type=float, default=20.0, help="Request timeout in seconds (default 20)")
    parser.add_argument("--retries", type=int, default=3, help="Number of retries for requests (default 3)")
    parser.add_argument("--backoff", type=float, default=1.0, help="Backoff factor for retries (default 1.0)")
    parser.add_argument("--no-https", action="store_true", help="Use HTTP instead of HTTPS (not recommended)")

    args = parser.parse_args()

    parsed = urlparse(args.url)
    domain = parsed.netloc if parsed.netloc else args.url
    domain = domain.strip().lower()
    if not domain:
        print("[module] [error] Invalid domain")
        return

    global BASE_CDX
    if args.no_https:
        BASE_CDX = BASE_CDX.replace("https://", "http://")

    session = build_session(retries=args.retries, backoff_factor=args.backoff)
    print(f"[module] [info] Fetching Wayback url for: {domain} (timeout={args.timeout}s, retries={args.retries})")
    urls = get_wayback_urls(session, domain, timeout=args.timeout)

    if urls:
        print(f"[module] [info] Found {len(urls)} unique URLs\n")
        if args.output or args.outpath:
            save_output(domain, urls, outpath=args.outpath)
    else:
        print("[module] [error] No URLs found or request timed out/failed.")

if __name__ == "__main__":
    main()
