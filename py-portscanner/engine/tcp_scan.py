import threading
import math
import socket

class TcpScan:
  def __init__(self, hosts, ports):
    self.hosts = hosts
    self.ports = ports
    self.port_groups = []
    self.hosts_scanned = 0
  
  def scan_single_port( host: str, port: int) -> bool:
    try:
      sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      sock.connect((host,port))
      sock.close()
      return True
    except:
      return False
      

  def getPortGroups(self):
    num_ports = len(self.ports)
    group_size = num_ports if num_ports % 2 == 0 else num_ports - 1

    port_group_size = math.floor(math.sqrt(group_size))

    i = 0
    while i <= num_ports:
      port_group = self.ports[i:port_group_size+i]
      i += port_group_size

      if i >= num_ports-1 and num_ports % 2 != 0:
        i = num_ports+2
        port_group.append(self.ports[len(self.ports)-1])
      self.port_groups.append(port_group)
    

  def scan_host(self):
    host: str = self.hosts[self.hosts_scanned]
    self.hosts_scanned += 1

    threads = []

    for i in self.port_groups:
      thrd = threading.Thread(target=TcpScan.scan_host_thread, kwargs={'host':host, 'ports':i})
      threads.append(thrd)

    for i in threads:
      i.start()
    
    for i in threads:
      i.join()

    
  def scan_host_thread(host, ports):
    for i in ports:
      if(TcpScan.scan_single_port(host,i)):
        print("%s:%d"%(host,i))