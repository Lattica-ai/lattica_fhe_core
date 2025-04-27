#!/usr/bin/env python3
import os
import subprocess
import sys

def build():
    """Execute the fhe_core_builder.sh script with 'python' argument."""
    script_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fhe_core_builder.sh")
    
    # Ensure the script is executable
    os.chmod(script_path, os.stat(script_path).st_mode | 0o111)
    
    # Execute the shell script with 'python' argument
    result = subprocess.run([script_path, "python"], check=False)
    
    # Return the exit code from the shell script
    return result.returncode

if __name__ == "__main__":
    sys.exit(build())
