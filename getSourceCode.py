import urllib2
from bs4 import BeautifulSoup
import os
import sys


header='http://wps.prenhall.com'
page = urllib2.urlopen(sys.argv[1])
soup = BeautifulSoup(page,'lxml')
hrefs=[link.get('href') for link in soup.find_all('a')]
sources = [s for s in hrefs if 'SourceCode' in s]
dirs=sys.argv[2]
if not os.path.isdir(dirs):
    os.system('mkdir '+dirs)
for s in sources:
    os.system("wget "+header+s)
os.system('mv *.c '+dirs+'/')
os.system('mv Makefile '+dirs+'/')
os.system('mv *.sh '+dirs+'/')
os.system('mv *.h '+dirs+'/')
