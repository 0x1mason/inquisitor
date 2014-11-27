import csv
import re

def remove_newline(s):
  s = s.replace('\n', ' ').replace('\r', '').replace('\t', '')
  return s

first_cap_re = re.compile('(.)([A-Z][a-z]+)')
all_cap_re = re.compile('([a-z0-9])([A-Z])')
default_re = re.compile('(?<=[d|D]efault ).+\w|(?<=[d|D]efaults to ).+\w', re.MULTILINE)

def convert(name):
    s1 = first_cap_re.sub(r'\1 \2', name)
    return all_cap_re.sub(r'\1 \2', s1).title()
    
def inferType(ex):
  ex = ex.split(" ")[0].strip(',').strip()
  print(ex)
  if "true" in ex or "false" in ex:
    return "bool"
  elif ex.isdigit():
    return "int"
  return "string"

def getDefault(des):
  m = default_re.search(des)
  if m is None or "current sim setting" in m.group(0):
    return ""
  s = m.group(0).strip()
  if s.startswith("is "):
    s = s[3:]
  return s

#csvfile = open('/Users/saucelabs/Documents/caps.csv', 'rb')
#spamreader = csv.reader(csvfile)
j = ''
with open('caps.csv', 'rb') as csvfile:
  spamreader = csv.reader(csvfile, delimiter=',', quotechar='"')
  for row in spamreader:
    if row[1] is not '':
      t = '{{"name": "{0}", "group": "{1}", "friendlyName": "{2}", "description": "{3}", "help": "{4}", "type": "{5}", "value": "{6}" }},\n '
      help = remove_newline(row[3]).replace("e.g. ", "").replace("e.g., ", "")
      j += t.format(row[1], row[0], convert(row[1]), remove_newline(row[2]), help, inferType(help), getDefault(remove_newline(row[2])))
j = '[' + j.strip(',') + ']'
f = open('caps_meta.json', 'w')
f.write(j)
f.close()
