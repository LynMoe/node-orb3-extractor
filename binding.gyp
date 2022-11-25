{
    "targets": [{
        "target_name": "module",
        'include_dirs': [
            './src',
            '$(OPENCV_INCLUDE_DIR) ',
            '/usr/local/include/opencv4',
        ],
        "cflags": [
            "-std=c++11",
        ],
        "cflags!": [
            "-fno-exceptions"
        ],
        "cflags_cc!": [
            "-fno-rtti",
            "-fno-exceptions"
        ],
        "ldflags": [
            "-Wl,-rpath,'$$ORIGIN'"
        ],
        "xcode_settings": {
            "OTHER_CFLAGS": [
                "-frtti",
                "-std=c++11",
                "-stdlib=libc++"
            ],
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
            "MACOSX_DEPLOYMENT_TARGET": "10.9"
        },
        'link_settings': {
            'libraries': [
                '-L/usr/local/lib ',
                '-L$(OPENCV_LIB_DIR) ',
                '-lopencv_core ',
                '-lopencv_imgproc ',
                '-lopencv_highgui ',
                '-lopencv_features2d ',
            ],
        },
        "sources": [
            "./src/wrapper.cpp",
            "./src/ORBextractor.cpp",
        ]
    }]
}
