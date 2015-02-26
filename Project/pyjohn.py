import serial, wave, struct, math
	
###############################################
### 			Binary Functions			###
###############################################

def int2bin(d):
	a = d >> 8
	b = d % (2 ** 8)
	out = [a,b]
	for i in range(2):
		if out[i] == 0:
			out[i] = 255
	
	return out

def bin2int(ls):
	if ls[0] == 255:
		a = 0
	else:
		a = ls[0] << 8
	
	return(a + ls[1])
			

###############################################
### 			Serial Functions			###
###############################################

def write2Bytes(length, ser):
	#print("write2")
	
	lengthArray = int2bin(length)
	
	for i in lengthArray:
		ser.write(chr(i))
		
	inp = ser.read()
	#print("confirming", inp)
	if inp != 'a':
		print "Error"

	
def write8Bytes(data, ser):
	#print("write8")
	if len(data) != 8:
		raise ValueError	
	
	for i in data:
		try:
			ser.write(chr(i))
		except ValueError:
			print("ValueError", i)
			quit()
	
	inp = ser.read()
	#print("confirming", inp)
	if inp != 'a':
		print "Error"
		
				
def writeDataBlock(data, ser):
	if(len(data)%8 != 0):
		for i in range(8-(len(data)%8)):
			data.append(1)
			
	while len(data) >= 8:
		current = data[0:8]
		data = data[8:]
		write8Bytes(current, ser)
		
		
def read2Bytes(ser):
	lengthArray = []
	
	for i in range(2):
		inp = ord(ser.read())
		lengthArray.append(inp)
		
	length = bin2int(lengthArray)
	
	ser.write('a')
	
	return(length)
		
		
def read8Bytes(ser):
	data = []
	
	for i in range(8):
		inp = ord(ser.read())
		data.append(inp)
	
	ser.write('a')
	
	return data
		
def readDataBlock(ser):
	length = read2Bytes(ser)

	data = []
	for i in range(length/8):
		current = read8Bytes(ser)
		for j in current:
			data.append(j)
	
	return data
	
	
###############################################
### 			Wave Functions				###
###############################################

def normWave(data):
	dataMax = max([math.fabs(min(data)), max(data)])
	maxVal = (1 << 16)
	maxFactor = maxVal / dataMax
	targetMax = 128
	
	for i in range(len(data)):
		data[i] = int(((float(data[i])*maxFactor)/maxVal)*targetMax)+targetMax
		if data[i] == 0:
			data[i] = 1


			
def writeWave(filename, ser):
	print("Sending wave")
	path = "Samples/" + filename
	print(path)
	wav = wave.open(path, 'r')
	data = []

	length = wav.getnframes()
	write2Bytes(length, ser)
	sampRate = wav.getframerate()
	write2Bytes(sampRate, ser)
	
	for i in range(0,length):
		waveData = wav.readframes(1)
		data.append(struct.unpack("<h", waveData)[0])
		
	wav.close()
	
	normWave(data)
	print "Data Length " + len(data)
	writeDataBlock(data, ser)
	
	print("Data sent")


###############################################
### 				Main					###
###############################################

ser = serial.Serial("/dev/ttyACM0")

while(1):
	if(ser.read() == 'z'):
		writeWave("coin2.wav", ser)


