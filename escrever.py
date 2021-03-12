import math

pz0= 25 
pz1= 100 
phi = [45,60,90] 
n = 50

particle = ["mu+", "mu-"]



def write_file(data,ang1):
   #já escreve o inicializador
   linha0 = "/run/initialize"
   data.write(linha0+"\n")
   #começa a calcular os valores
   ang = [30,50,70,90]
   for ang0k in ang:
      ang0=ang0k/10
      for pz in range(pz0,pz1,5): 
       	pt = (pz/10)*math.tan(math.pi*ang0/180)
       	px=pt/(math.sqrt(1+math.tan(math.pi*ang1/180)*math.tan(math.pi*ang1/180)))
       	py = px*math.tan(math.pi*ang1/180)
       	#escreve o comentário no arquivo indicando o ângulo
       	linha02 = "#{0},{1}".format(ang0, ang1) 
       	data.write(linha02+"\n")
       	#Após calculado, escrever para mu+ e mu-
       	for part in particle:
           linha_mu = "/gun/particle {0}".format(part)
           linha1 = "/gun/momentum {0} {1} {2}".format((px),(py),(pz/10))
           linha2 = "/run/beamOn {0}".format(n)
           data.write(linha_mu + "\n")
           data.write(linha1+"\n")
           data.write(linha2+"\n")

	

for i in phi:
   filename = "events{0}.in".format(i)
   data = open(filename, "w")
   write_file(data,i)
   data.close()

