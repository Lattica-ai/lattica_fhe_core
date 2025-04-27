# Integration Guide for Lattica FHE Core Packaging

This guide explains how to transition from direct copying of build artifacts to using proper packaging with Poetry and npm.

## Initial Setup

1. Make sure you have these installed on your system:
- **Poetry**  
  Manages Python dependencies and packaging.

- **npm**  
  Installs JavaScript packages needed by the project.

- **Python Build Dependencies**  
  These libraries are used in our build scripts:
  - **tomli**: Parses TOML files (configuration files).
  - **tomli-w**: Writes TOML files.
  - **twine**: Uploads Python packages to PyPI securely.

2. Update the version in `version.toml` when you want to create a new release:

   ```toml
   [package]
   version = "0.1.0"  # Change this to your new version
   ```

3. Run the version updater to propagate the version to all configuration files: ( *For future use )
   ```bash
   python update_versions.py
   ```

## Building Packages

To generate wheel packages and npm package:  ( *This is for future use, currently we don't use it )

```bash
./fhe_core_builder.sh wheels
```

This will:

1. Build the Python modules (same as `./fhe_core_builder.sh python`)
2. Build the WASM modules (same as `./fhe_core_builder.sh wasm`)
3. Package them into:
   - `dist/lattica_fhe_core-<version>-cp312-cp312-manylinux_2_28_x86_64.whl`
   - `dist/lattica_fhe_core_deep-<version>-cp312-cp312-manylinux_2_28_x86_64.whl`
   - `dist/cpp_sdk.wasm` and `dist/cpp_sdk.js` (npm package artifacts)

## Publishing to AWS CodeArtifact ( *For future use )

To publish the packages to AWS CodeArtifact:

```bash
python publish_to_codeartifact.py --domain <domain> --owner <account-id> --repository <repo-name> --region <aws-region>
```

## Updating Client Repositories

### For Python Projects

Update the client and lattice-toolkit repositories to use Poetry and install from CodeArtifact:

```toml
# In pyproject.toml
[tool.poetry.dependencies]
lattica-fhe-core = "^0.1.0"
```

Or for the deep binding:

```toml
# In pyproject.toml
[tool.poetry.dependencies]
lattica-fhe-core-deep = "^0.1.0"
```

### For JavaScript/TypeScript Projects

Update the lattica-query-client repository to use npm and install from CodeArtifact:

```json
// In package.json
{
  "dependencies": {
    "lattica-fhe-core-wasm": "^0.1.0"
  }
}
```
