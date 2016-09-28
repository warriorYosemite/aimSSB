import requests
import pprint
import xml.etree.ElementTree as etree
from HTMLParser import HTMLParser

class SSBParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        for t,a in self.to_store:
            if t == tag and (len(attrs)==0 or a in attrs[0]):
                self.to_return.append({str(tag):None})
                self.switch = True
    def handle_data(self, data):
        if self.switch:
            d = self.to_return[-1]
            d[d.keys()[0]] = data
            self.to_return[-1] = d
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
parser = SSBParser()
all_data = []
for url in all_urls:
    html_resp = requests.get(url).text
    scraped_data = L_scrape(html_resp, (("h1", "entry-title"),("span", "EN-IN"),("p", "")) , url, parser)
    all_data.append(scraped_data)
##########################################################################################################
pprint.pprint(all_data)
