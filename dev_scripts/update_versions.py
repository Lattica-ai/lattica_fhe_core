#!/usr/bin/env python3
import os
import tomli
import tomli_w
import json
import re

# Get the absolute path to the script's directory
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, ".."))

def read_version():
    version_path = os.path.join(PROJECT_ROOT, "version.toml")
    with open(version_path, "rb") as f:
        version_data = tomli.load(f)
    return version_data["package"]["version"]

def update_pyproject_toml(version):
    """Update version in pyproject.toml files"""
    # Update for regular binding
    pyproject_path = os.path.join(PROJECT_ROOT, "pyproject.toml")
    if os.path.exists(pyproject_path):
        with open(pyproject_path, "rb") as f:
            pyproject = tomli.load(f)
        
        pyproject["tool"]["poetry"]["version"] = version
        
        with open(pyproject_path, "wb") as f:
            tomli_w.dump(pyproject, f)
    
    # Update for deep binding
    pyproject_deep_path = os.path.join(PROJECT_ROOT, "pyproject_deep.toml")
    if os.path.exists(pyproject_deep_path):
        with open(pyproject_deep_path, "rb") as f:
            pyproject_deep = tomli.load(f)
        
        pyproject_deep["tool"]["poetry"]["version"] = version
        
        with open(pyproject_deep_path, "wb") as f:
            tomli_w.dump(pyproject_deep, f)

def update_package_json(version):
    """Update version in package.json"""
    package_path = os.path.join(PROJECT_ROOT, "package.json")
    if os.path.exists(package_path):
        with open(package_path, "r") as f:
            package_data = json.load(f)
        
        package_data["version"] = version
        
        with open(package_path, "w") as f:
            json.dump(package_data, f, indent=2)

def update_cmake_version(version):
    """Update version in CMakeLists.txt"""
    cmake_path = os.path.join(PROJECT_ROOT, "CMakeLists.txt")
    if os.path.exists(cmake_path):
        with open(cmake_path, "r") as f:
            cmake_content = f.read()
        
        # Check if version is already defined
        version_match = re.search(r'project\(LatticaCppSdk VERSION \d+\.\d+\.\d+\)', cmake_content)
        if version_match:
            new_cmake_content = re.sub(
                r'project\(LatticaCppSdk VERSION \d+\.\d+\.\d+\)', 
                f'project(LatticaCppSdk VERSION {version})', 
                cmake_content
            )
        else:
            # If no VERSION in project(), add it
            new_cmake_content = re.sub(
                r'project\(LatticaCppSdk\)',
                f'project(LatticaCppSdk VERSION {version})',
                cmake_content
            )
        
        with open(cmake_path, "w") as f:
            f.write(new_cmake_content)

def main():
    version = read_version()
    print(f"Updating all project files to version: {version}")
    
    update_pyproject_toml(version)
    update_package_json(version)
    update_cmake_version(version)
    
    print("Version update complete")

if __name__ == "__main__":
    main()