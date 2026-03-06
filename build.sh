#!/bin/bash

# Default values
BUILD_TYPE="Debug"
OUT_DIR="build"
EXE_NAME="my_project"
RUN_AFTER_BUILD=false
IS_DIST=false

usage() {
    echo "Usage: $0 [-r] [-o dir] [-n name] [--release | --minsize | --dist]"
    echo "  -r         : Run after build"
    echo "  -o         : Output directory (default: build)"
    echo "  -n         : Executable name"
    echo "  --release  : Standard optimized build"
    echo "  --minsize  : Optimized for smallest binary size"
    echo "  --dist     : Clean standalone distribution (Exe + Data only)"
    exit 1
}

# Parse flags
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -r) RUN_AFTER_BUILD=true ;;
        -o) OUT_DIR="$2"; shift ;;
        -n) EXE_NAME="$2"; shift ;;
        --release) BUILD_TYPE="Release" ;;
        --minsize) BUILD_TYPE="MinSizeRel" ;;
        --dist)    BUILD_TYPE="Release"; IS_DIST=true; OUT_DIR="dist" ;;
        -h|--help) usage ;;
        *) echo "Unknown parameter: $1"; usage ;;
    esac
    shift
done

FINAL_BUILD_DIR="$OUT_DIR/$BUILD_TYPE"

# If Distribution mode, wipe the old folder to ensures a "clean" slate
if [ "$IS_DIST" = true ]; then
    echo "!!! Preparing Clean Distribution Build !!!"
    rm -rf "$FINAL_BUILD_DIR"
fi

mkdir -p "$FINAL_BUILD_DIR"

# Step 1: Build
cmake -S . -B "$FINAL_BUILD_DIR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build "$FINAL_BUILD_DIR" --config $BUILD_TYPE

# Step 2: Distribution Cleanup & Asset Copying
if [ "$IS_DIST" = true ]; then
    echo "--- Finalizing Distribution Folder ---"

    # Copy Data folder if it exists
    if [ -d "./Data" ]; then
        cp -r "./Data" "$FINAL_BUILD_DIR/"
        echo "Successfully copied /Data to $FINAL_BUILD_DIR"
    else
        echo "Warning: /Data folder not found. Skipping copy."
    fi

    # Cleanup: Remove CMake internal files to leave only the Exe and Data
    # This keeps the folder 'shippable'
    find "$FINAL_BUILD_DIR" -maxdepth 1 -not -name "$EXE_NAME" -not -name "Data" -not -name "$BUILD_TYPE" -delete
    echo "Cleanup complete. Folder '$FINAL_BUILD_DIR' is ready for zip/shipping."
fi

# Step 3: Run logic
if [ "$RUN_AFTER_BUILD" = true ]; then
    TARGET_PATH="./$FINAL_BUILD_DIR/$EXE_NAME"
    if [ -f "$TARGET_PATH" ]; then
        echo "--- Executing $EXE_NAME ---"
        "$TARGET_PATH"
    else
        echo "Error: Executable $EXE_NAME not found."
        exit 1
    fi
fi