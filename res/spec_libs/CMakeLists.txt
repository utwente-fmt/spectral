# Target that rebuilds the specification-library for Swift
add_custom_target(BuildSwiftLib # ALL
    COMMAND swift build --package-path ${CMAKE_SOURCE_DIR}/res/spec_libs/swift/PallasSpec
    COMMENT "Building Swift specification library"
)

# Alternatively, we could use swiftc directly
# COMMAND swiftc -emit-library -emit-module -module-name PallasSpec -o MyModule.a MyModule/Sources/*.swift

# Target that builds the specification-library for Rust.
add_custom_target(BuildRustLib 
    COMMAND cargo build 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/res/spec_libs/rust/rust_spec
    COMMENT "Building Rust specification library"
) 

