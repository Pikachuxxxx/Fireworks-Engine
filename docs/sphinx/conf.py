import subprocess
subprocess.call('cd .. ; doxygen', shell=True)
html_extra_path = ['../html']
