import subprocess, os

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'
if read_the_docs_build:
    subprocess.call('cd .. ; doxygen', shell=True)

html_extra_path = ['../build/html']
html_theme = "sphinx_rtd_theme"
master_doc = 'index'
