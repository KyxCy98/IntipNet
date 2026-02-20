import shutil
import sys

def check_requirements():
    modules = ["nmap", "subfinder", "httpx"]
    missing = []

    for tool in modules:
        if shutil.which(tool) is None:
            missing.append(tool)

    if missing:
        print("\n     IntipNet requires an additional module. Please install it manually or using install.sh.")
        print(f"     Module Missing: {', '.join(missing)}")
        print("     Please install it first so that it can be run.")
        sys.exit(1)

if __name__ == "__main__":
    check_requirements()