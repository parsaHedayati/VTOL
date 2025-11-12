from setuptools import find_packages
from setuptools import setup

setup(
    name='custom_vtol_plugin',
    version='0.0.1',
    packages=find_packages(
        include=('custom_vtol_plugin', 'custom_vtol_plugin.*')),
)
