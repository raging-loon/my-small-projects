import options
import engine.tcp_scan
# extern
global_options = options.ps_options()




def main():
  global_options.parse_options()
  scanner = engine.tcp_scan.TcpScan(global_options.ipv4addrs, global_options.ports)

  scanner.getPortGroups()
  

if __name__ == '__main__':
  main()