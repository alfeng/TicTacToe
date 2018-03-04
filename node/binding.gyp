{
  'targets': [{
    'target_name': "TicTacToeV8",

    'include_dirs': [
      "<!(node -e \"require('nan')\")",
	  "./src"
    ],

    'cflags': [
      "-Wall", "-std=c++11"
    ],

    'conditions': [
      ['OS=="linux"', {
        'defines': [
          "__CGDV_PLATFORM_ANDROID__"
        ],
      }], #'OS=="linux"'

      ['OS=="mac"', {
        'defines': [
          "__CGDV_PLATFORM_IOS__"
        ],
        'xcode_settings': {
          "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++"],
          "OTHER_LDFLAGS": ["-stdlib=libc++"],
          "MACOSX_DEPLOYMENT_TARGET": "10.7"
        }
      }], #'OS=="mac"'

      ['OS=="win"', {
        'defines': [
          "__CGDV_PLATFORM_WIN32__",
          "__CGDV_ENABLE_TRACE__",
          "_MBCS", "WIN32", "_WIN32", "NDEBUG",
          "_HAS_EXCEPTIONS=1",
          "_CRT_SECURE_NO_WARNINGS",
          "_CRT_SECURE_NO_DEPRECATE",
          "_CRT_NON_CONFORMING_SWPRINTFS",
          "_DAS_URL_=\"https://dev.cgtglobal.com/das/v3/\"",
          "_APP_HASH_=\"DEV_HASH\""
        ],

        'include_dirs': [
          "../include/win32",
          "../include/common",
          "../include/common/das",
          "../poco/include",
          "../openssl/include"
        ],

        'library_dirs': [
          "../libs/x64/release",
          "../poco/libs/x64/release",
          "../openssl/lib/x64/release"
        ],

        'libraries': [
          "-lcgdv.lib", "-lIphlpapi.lib", "-lWs2_32.lib", "-lcrypt32.lib",
          "-lPocoCrypto.lib", "-lPocoFoundation.lib", "-lPocoJSON.lib",
          "-lPocoNet.lib", "-lPocoUtil.lib", "-lPocoXML.lib", "-lPocoZip.lib"
        ],

#        'cppflags': [
#          '/WX-', '/MP', '/GS', '/TP', '/W3', '/Zi', '/m', '/X',
#          '/Gm-', '/O2', '/Oy-', '/Gd', '/MT', '/Zc:wchar_t',
#          '/EHsc', '/analyze-', '/fp:precise', '/Zc:forScope',
#          '/errorReport:prompt', '/nologo'
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
      "./src/v8CgdvStatus.cpp",
      "./src/cgdvV8.cpp",
      "./src/CgdvApp.cpp"
    ]

  }] # 'targets'
}
