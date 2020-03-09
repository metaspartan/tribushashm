from setuptools import setup, Extension

tribushashm_module = Extension('tribushashm',
                               sources = ['tribusmodule.c',
                                          'tribus.c',
										  'sph/aes_helper.c',
										  'sph/sph_jh.c',
										  'sph/sph_keccak.c',
										  'sph/sph_echo.c'],
                               include_dirs=['.', './sph'])

setup (name = 'tribushashm',
       version = '1.0',
       description = 'Bindings for tribus proof of work used by Denarius',
       ext_modules = [tribushashm_module])
