import requests
import pprint
import xml.etree.ElementTree as etree
from HTMLParser import HTMLParser

def get_val(it, tp):
    for t in tp:
        it = it.__getitem__(t)
    return it

class SSBParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        for t,a,n,ln in self.to_store:
            if t == tag and (len(attrs)==0 or a in attrs[0]):
                if n!=None:
                    val = get_val(attrs,n)
                else:
                    val = str(tag)
                if len(val) > ln:
                    self.to_return.append(val)
                    self.switch = True
    def handle_data(self, data):
        if self.switch:
            self.to_return[-1] = {self.to_return[-1]:data}
            self.switch = not self.switch
    def tag_wrap(self, to_store):
        self.to_store  = to_store
        self.to_return = []
        self.switch    = False

def L_scrape(html_resp, to_store, url, parser):
    parser.tag_wrap(to_store)
    parser.feed(html_resp)
    d = {"url":url}
    data = parser.to_return
    d["data"] = data
    return d

########################## GET ALL URLS FROM XML ###########
all_urls = set(list())
start_url = "http://www.ssbcrack.com/post.xml"
post_xml  = requests.get(start_url).text
urlset      = etree.fromstring(post_xml)
for url in urlset:
    all_urls.add(url[0].text)
all_urls = tuple(all_urls)
###########################################################

########################## PARSE ALL URLS AND GET CONTENTS ################################################
data_to_scrape = (
                    ("meta",   "description", (1,1), -1),
                    ("h1",     "entry-title", None,  -1),
                    ("span",   "EN-IN",       None,   5),
                    ("p",      "",            None,   5),
                    ("title",  "",            None,  -1)
                )
parser = SSBParser()
all_data = []
for url in all_urls[0:1]:
    html_resp = requests.get(url).text
    scraped_data = L_scrape(html_resp, data_to_scrape , url, parser)
    all_data.append(scraped_data)
##########################################################################################################
pprint.pprint(all_data)
