#!/usr/bin/env python3
import os
import subprocess
import tomli
import argparse
import json
import sys
from pathlib import Path

def read_version():
    script_dir = Path(__file__).resolve().parent
    version_file = script_dir / "../version.toml"
    with open(version_file, "rb") as f:
        version_data = tomli.load(f)
    return version_data["package"]["version"]

def run_command(cmd, error_msg=None):
    """Run a command and handle errors"""
    try:
        subprocess.run(cmd, check=True)
    except subprocess.CalledProcessError as e:
        if error_msg:
            print(f"Error: {error_msg}")
        print(f"Command failed with exit code {e.returncode}: {' '.join(cmd)}")
        sys.exit(1)

def publish_python_wheels(domain, owner, repository, region, wheels_dir="dist"):
    """Publish Python wheels to AWS CodeArtifact"""
    print("Publishing Python wheels to AWS CodeArtifact...")
    
    # Get token for AWS CodeArtifact
    token_cmd = [
        "aws", "codeartifact", "get-authorization-token",
        "--domain", domain,
        "--domain-owner", owner,
        "--query", "authorizationToken",
        "--output", "text",
        "--region", region
    ]
    
    result = subprocess.run(token_cmd, capture_output=True, text=True, check=True)
    token = result.stdout.strip()
    
    # Get the repository endpoint
    endpoint_cmd = [
        "aws", "codeartifact", "get-repository-endpoint",
        "--domain", domain,
        "--domain-owner", owner,
        "--repository", repository,
        "--format", "pypi",
        "--query", "repositoryEndpoint",
        "--output", "text",
        "--region", region
    ]
    
    result = subprocess.run(endpoint_cmd, capture_output=True, text=True, check=True)
    endpoint = result.stdout.strip()
    
    # Find all wheel files
    wheel_files = [f for f in os.listdir(wheels_dir) if f.endswith('.whl')]
    
    for wheel in wheel_files:
        wheel_path = os.path.join(wheels_dir, wheel)
        publish_cmd = [
            "pip", "install", "--no-deps", "--index-url", endpoint,
            "--extra-index-url", "https://pypi.org/simple",
            wheel_path
        ]
        
        env = os.environ.copy()
        env["TWINE_USERNAME"] = "aws"
        env["TWINE_PASSWORD"] = token
        env["TWINE_REPOSITORY_URL"] = endpoint
        
        # Use twine to upload the wheel
        twine_cmd = ["twine", "upload", wheel_path]
        
        print(f"Publishing {wheel}...")
        run_command(twine_cmd, f"Failed to publish {wheel} to AWS CodeArtifact")

def publish_npm_package(domain, owner, repository, region):
    """Publish npm package to AWS CodeArtifact"""
    print("Publishing npm package to AWS CodeArtifact...")
    
    # Configure npm to use AWS CodeArtifact
    config_cmd = [
        "aws", "codeartifact", "login",
        "--tool", "npm",
        "--domain", domain,
        "--domain-owner", owner,
        "--repository", repository,
        "--region", region
    ]
    
    run_command(config_cmd, "Failed to configure npm for AWS CodeArtifact")
    
    # Publish the package
    publish_cmd = ["npm", "publish"]
    run_command(publish_cmd, "Failed to publish npm package to AWS CodeArtifact")

def main():
    parser = argparse.ArgumentParser(description="Publish packages to AWS CodeArtifact")
    parser.add_argument("--domain", required=True, help="CodeArtifact domain")
    parser.add_argument("--owner", required=True, help="CodeArtifact domain owner (AWS account ID)")
    parser.add_argument("--repository", required=True, help="CodeArtifact repository name")
    parser.add_argument("--region", required=True, help="AWS region")
    parser.add_argument("--type", choices=["python", "npm", "all"], default="all",
                        help="Type of package to publish (python, npm, or all)")
    
    args = parser.parse_args()
    
    version = read_version()
    print(f"Publishing version {version} to AWS CodeArtifact")
    
    if args.type in ["python", "all"]:
        publish_python_wheels(args.domain, args.owner, args.repository, args.region)
    
    if args.type in ["npm", "all"]:
        publish_npm_package(args.domain, args.owner, args.repository, args.region)
    
    print("Publishing complete!")

if __name__ == "__main__":
    main()