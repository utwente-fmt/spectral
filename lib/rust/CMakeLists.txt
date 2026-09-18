# Library that contains the C++-specific aspects of the specification translation
add_library(spec2ir_Rust STATIC
    RustCompilerDriver.cpp
    RustSpecTransformer.cpp
    RustSpecUnifier.cpp
    RustSyntaxResolver.cpp
    RustWrapperGenerator.cpp
)
         
target_include_directories(spec2ir_Rust PUBLIC
    "${CMAKE_SOURCE_DIR}/include/rust"
)

target_link_libraries(spec2ir_Rust
        ${llvm_libs} 
        spec2ir_core
)