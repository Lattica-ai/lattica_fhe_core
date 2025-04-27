# Import the compiled module
try:
    from .cpp_sdk import *
    __all__ = ["cpp_sdk"]
except ImportError:
    import sys
    sys.stderr.write("Error importing lattica_fhe_core. Please ensure the package is properly installed.\n")
    raise