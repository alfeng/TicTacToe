{
  'targets': [{
    'target_name': "tic-tac-toe",

    'include_dirs': [
      "<!(node -e \"require('nan')\")",
	  "../common"
    ],

    'cflags': [
      "-Wall", "-std=c++11"
    ],

    'conditions': [
      ['OS=="linux"', {
        'defines': [
          "___PLATFORM_LINUX__"
        ],

        'include_dirs': [
          "../common"
        ]
      }], #'OS=="linux"'

      ['OS=="mac"', {
        'defines': [
          "__PLATFORM_IOS__"
        ],
        'xcode_settings': {
          "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++"],
          "OTHER_LDFLAGS": ["-stdlib=libc++"],
          "MACOSX_DEPLOYMENT_TARGET": "10.7"
        }
      }], #'OS=="mac"'

      ['OS=="win"', {
        'defines': [
          "_MBCS", "WIN32", "_WIN32", "NDEBUG",
          "_HAS_EXCEPTIONS=1",
          "_CRT_SECURE_NO_WARNINGS",
          "_CRT_SECURE_NO_DEPRECATE",
          "_CRT_NON_CONFORMING_SWPRINTFS"
        ],

        'include_dirs': [
          "../common"
        ],

        'configurations': {
          'Release': {
            'msvs_settings': {
              'VCCLCompilerTool': {
                'ExceptionHandling': 1
              },

              'VCLinkerTool': {
                'GenerateDebugInformation': "false",
                ]
              }
            } # 'msvs_settings'
          } # 'Release'
        } # 'configurations'

      }], #'OS=="win"'
    ], # 'conditions'

    'sources': [
      "./TicTacToeV8.cpp",
      "../common/CTiTacToe.cpp",
      "../common/TurnLog.cpp"
    ]

  }] # 'targets'
}
