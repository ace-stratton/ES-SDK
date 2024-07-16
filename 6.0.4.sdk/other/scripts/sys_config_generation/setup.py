import pathlib
from setuptools import setup, find_packages

# The directory containing this file
HERE = pathlib.Path(__file__).parent

# The text of the README file
INFO = (HERE / "README").read_text()

# Package meta-data.
NAME = 'es-sys-config'
DESCRIPTION = 'Generation of the configuration file for the OBC'
URL = 'https://gitlab.endurosatlab.com/sw-platform-es/modules/on-boardcomputer/stm32f/obc-stdpf-hw-1.x'
EMAIL = 'support@endurosat.com'
AUTHOR = 'Endurosat SW Platform'
REQUIRES_PYTHON = '>=3.9.0'
VERSION = '2.0.2'

# What packages are required for this module to be executed?
REQUIRED = [
    'typer',
    'colorama',
    'shellingham',
]

# What packages are optional?
EXTRAS = {
    # 'fancy feature': ['django'],
}

# This call to setup() does all the work
setup(
    name=NAME,
    version=VERSION,
    description=DESCRIPTION,
    long_description=INFO,
    long_description_content_type="text/markdown",
    python_requires=REQUIRES_PYTHON,
    url=URL,
    author=AUTHOR,
    author_email=EMAIL,
    license="All rights reserved",
    classifiers=[
        "License :: Other/Proprietary License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.9",
    ],
    packages=find_packages(exclude=["tests", "*.tests", "*.tests.*", "tests.*"]),
    include_package_data=True,
    install_requires=REQUIRED,
    extras_require=EXTRAS,
    entry_points={
        "console_scripts": [
            "es-sys-config=es_sys_config.__main__:main",
        ]
    },
)
