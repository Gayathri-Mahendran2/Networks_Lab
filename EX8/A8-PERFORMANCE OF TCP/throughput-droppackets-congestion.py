def find_through_output(s,e):
	f=open("out.tr",'r')
	flag=0
	count=0
	et,st,th=0,0,0
	for i in f:
		out=i.split( " ")
		if(int(out[2])==s and int(out[3])==e ):
			if flag==0 :
				st=float(out[1])
				flag=1
			if(out[0]=='r'):
				count+=1
			et=float(out[1])
	time=(et-st)*1000
	if(count!=0):
		th=time/count
		print("%-5d %-5d %10f %10d %15f"%(s,e,time,count,th))
num=int(input("Enter num of nodes: "))
print("From  To    Time in ms   nodes received  Throughoutput")
for i in range (num):
	for j in range (num):
		find_through_output(i,j)
f=open("out.tr",'r')
drop=0
for i in f:
	out=i.split( " ")
	if(out[0]=='d'):
		drop+=1
print("Number of dropped packets:",drop)	 
