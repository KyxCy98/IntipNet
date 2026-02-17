import yaml
import json
import sys
from pathlib import Path

base = Path(__file__).resolve().parent
def find(base: path):
    for p in base.rglob("templates"):
        if p.is_dir():
            return p
    return None

template = find(base)

if not template:
    print(file=sys.stderr)
    sys.exit(1)

with open(base / "engine.yml") as f:
    config = yml.safe_load(f)

config["template"] = str(template)

print(json.dumps(config))
