# Import the compiled module
try:
    from .cpp_sdk_with_deep_binding import *
    __all__ = ["cpp_sdk_with_deep_binding"]
except ImportError:
    import sys
    sys.stderr.write("Error importing lattica_fhe_core_deep. Please ensure the package is properly installed.\n")
    raise