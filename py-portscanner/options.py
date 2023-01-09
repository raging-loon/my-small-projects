from engine.error import ps_exit
import argparse
import ipaddress

"""
  Holds all of the options for the program
"""
class ps_options:
  def __init__(self):
    self.protocol = None
    self.ipv4addrs = []
    self.ipv6addrs = []
    self.ports = []
    self.arguments = None


  """ 
    Parse command line arguments
  """
  def parse_options(self):  
    parser = argparse.ArgumentParser()

    parser.add_argument("-i","--ipaddrs",help="IP Addresses to scan")
    parser.add_argument("-4","--ipv4", action="store_true", help="Scan IPv4")
    parser.add_argument("-6","--ipv6", action="store_true", help="Scan IPv6")
    parser.add_argument("-p","--ports", help="Ports")
  
    self.arguments = parser.parse_args()

    if(self.arguments.ports == None):
      ps_exit("Need ports to scan", 1)
    else:
      self.parse_port_str(self.arguments.ports)
      print(self.ports)

    if(self.arguments.ipv4 == False and self.arguments.ipv6 == False):
      ps_exit("Must specify IPv4(-4) or IPv6(-6)", 1)
    
    if(self.arguments.ipaddrs == None):
      ps_exit("Need address[es] to scan", 1)
    else:
      if(self.arguments.ipv4): self.parse_ipv4_addrs(self.arguments.ipaddrs)
      elif(self.arguments.ipv6): pass




  """ 
    Add a single port to self.ports unless the port is already present 
  """
  def add_port(self,port: int):
    if(port not in self.ports):
      self.ports.append(port)

  """ 
    Parse a port string, e.g. '80,443,136-139'
  """
  def parse_port_str(self, portstr: str): 
    # TODO: ADD ERROR HANDLING
    for i in portstr.split(","):
      if('-' in i):
        spl = i.split("-")
        for x in range(int(spl[0]), int(spl[1])+1):
          self.add_port(int(x))
      else:
        self.add_port(int(i))


  """
    Use the ipaddress module to determine if addr_str
    is a valid IPv4 address
  """
  def is_valid_ipv4_address(self, addr_str: str) -> bool:
    try:
      ipaddress.IPv4Address(addr_str)
      return True
    except:
      return False


  """
    Call our other ipv4 parsing functions based on the strings contents
  """
  def parse_ipv4_addrs(self, ipv4_addr_list: str): 
    if("," in ipv4_addr_list): self.parse_ipv4_list(ipv4_addr_list)
    elif ("-" in ipv4_addr_list): self.parse_ipv4_range(ipv4_addr_list)
    elif ("/" in ipv4_addr_list): self.parse_ipv4_cidr(ipv4_addr_list)
    else: self.parse_ipv4_list(ipv4_addr_list)

    print(self.ipv4addrs)



  """
    Parse and IPv4 address range, i.e. 192.168.0.1-255
  """
  def parse_ipv4_range(self, ipv4_addr_list: str): 
    # check the last octet for the range
    if(not ipv4_addr_list.split(".")[-1].__contains__('-')):
      ps_exit("Invalid IPv4 range: %s"%(ipv4_addr_list), 1)
    
    begin, end = ipv4_addr_list.split(".")[-1].split("-")

    # get the address minus the last octet
    base_addr = ipv4_addr_list[:ipv4_addr_list.rindex('.')+1]
    
    # check that begin and end are numbers and they fall with in the octet range
    # then make sure end is larger than begin
    if not begin.isnumeric() or not end.isnumeric() \
       or int(begin) > 255 or int(begin) < 0 or int(end) > 255 or int(end) < 0 or int(end) < int(begin):
      ps_exit("Invalid IPV4 range: %s"%(ipv4_addr_list), 1)
    
    for i in range(int(begin), int(end)+1):
      if(not self.is_valid_ipv4_address(base_addr + str(i))):
        ps_exit("Invalid IPV4 range: %s"%(ipv4_addr_list), 1)
      else:
        self.ipv4addrs.append(base_addr + str(i))
      

  """
    Parse a CIDR range, i.e 192.168.0.1/25
  """
  def parse_ipv4_cidr(self, ipv4_addr_list: str):
    ipv4Network = None
    try:
      ipv4Network = ipaddress.IPv4Network(ipv4_addr_list)
    except:
      ps_exit("Invalid CIDR range: %s"%(ipv4_addr_list), 1)

    for addr in ipv4Network.hosts():
      self.ipv4addrs.append(addr.__str__())


  """
    Parse a list of IPv4 addresses, i.e. 192.168.0.1, 8.8.8.8, 1.1.1.1
  """
  def parse_ipv4_list(self, ipv4_addr_list: str): 
    for addr in ipv4_addr_list.split(","):
      if not self.is_valid_ipv4_address(addr):
        ps_exit("Not a valid IPv4 address: %s"%(addr), 1)
      self.ipv4addrs.append(addr)
    

