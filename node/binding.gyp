{
  'targets': [{
    'target_name': "TicTacSvc",

    'include_dirs': [
      "<!(node -e \"require('nan')\")",
	  "../common",
	  "./src"
    ],

    'cflags': [
#      "-Wall", "-std=c++11", "-m64", "-fPIC", "-frtti", "-fexceptions"
      "-Wall", "-std=c++11", "-fPIC"
    ],

    'ldflags': [
#      "-Wl,-z,defs",
#      "-Wl,--export-dynamic"
    ],

    'conditions': [
      ['OS=="mac"', {
        'xcode_settings': {
          "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++"],
          "OTHER_LDFLAGS": ["-stdlib=libc++"],
          "MACOSX_DEPLOYMENT_TARGET": "10.7"
        }
      }], #'OS=="mac"'

      ['OS=="linux"', {
        'include_dirs': [
          "<!(pwd)/../common",
          "<!(pwd)/src",
        ],
      }], #'OS=="linux"'

      ['OS=="win"', {
        'defines': [
          "_MBCS", "WIN32", "_WIN32", "NDEBUG",
          "_HAS_EXCEPTIONS=1",
          "_CRT_SECURE_NO_WARNINGS",
          "_CRT_SECURE_NO_DEPRECATE",
          "_CRT_NON_CONFORMING_SWPRINTFS"
        ],

#        'include_dirs': [
#          "<!(pwd)/../common",
#          "<!(pwd)/src",
#        ],

        'configurations': {
          'Release': {
            'msvs_settings': {
              'VCCLCompilerTool': {
                'ExceptionHandling': 1
              },

              'VCLinkerTool': {
                'GenerateDebugInformation': "false",

                'IgnoreDefaultLibraryNames': [
                  "PocoCryptoMT.lib", "PocoFoundationMT.lib", "PocoJSONMT.lib", "PocoNetMT.lib",
                  "PocoNetSSLMT.lib", "PocoUtilMT.lib", "PocoXMLMT.lib", "PocoZipMT.lib"
                ]
              }
            } # 'msvs_settings'
          } # 'Release'
        } # 'configurations'

      }], #'OS=="win"'
    ], # 'conditions'

    'sources': [
      "../common/CTicTacToe.cpp",
      "../common/TurnLog.cpp",
      "./src/TicTacToeV8.cpp"
    ]
  },  # TicTacSvc target

  {
      "target_name": "copy_binary",
      "type": "none",
      "dependencies" : [ "TicTacSvc" ],
      "copies": [{
        'destination': '<(module_root_dir)',
        'files': ['<(module_root_dir)/build/Release/TicTacSvc.node']
      }]
  }  # copy target

  ] # 'targets'
}

