import serial, wave, struct


###############################################
### 			Wave Functions				###
###############################################
def readWav(filename):
	wav = wave.open(("Samples/"+filename), 'r')
	data = []

	length = wav.readnframes()
	for i in range(0,10000):
		waveData = wav.readframes(1)
		data.append(struct.unpack("<h", waveData)[0])
		
	wav.close()
	
	normWave(data)
	
	return data

def normWave(data):
	maxVal = float(max(data))
	for i in range(len(data)):
		data[i] = int(((data[i]+maxVal)/(2*maxVal)) * 255)
		if data[i] == 0:
			data[i] += 1
	
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

def writeLen(length, ser):
	
	lengthArray = int2bin(length)
	
	for i in lengthArray:
		ser.write(chr(i))
		#print(ord(ser.read()))
		
	inp = ser.read()
	if inp != 'a':
		print "Error"
		
def readLen(ser):
	lengthArray = []
	
	for i in range(2):
		inp = ord(ser.read())
		lengthArray.append(inp)
		
	length = bin2int(lengthArray)
	
	ser.write('a')
	
	return(length)
	
	
def write8Bytes(data, ser):

	if len(data) != 8:
		raise ValueError	
	
	for i in data:
		ser.write(chr((i%100)+1))
		
	inp = ser.read()
	if inp != 'a':
		print "Error"
		
def read8Bytes(ser):
	data = []
	
	for i in range(8):
		inp = ord(ser.read())
		data.append(inp)
	
	ser.write('a')
	
	return data

def writeDataBlock(data, ser):
	if(len(data)%8 != 0):
		for i in range(8-(len(data)%8)):
			data.append(1)
	
	writeLen(len(data), ser)
	
	while len(data) >= 8:
		current = data[0:8]
		data = data[8:]
		write8Bytes(current, ser)
		
def readDataBlock(ser):
	length = readLen(ser)

	data = []
	for i in range(length/8):
		current = read8Bytes(ser)
		for j in current:
			data.append(j)
	
	return data

###############################################
### 				Main					###
###############################################

ser = serial.Serial("/dev/ttyACM0")
data = []
for i in range(1000):
	data.append((i))

writeDataBlock(data, ser)
data2 = readDataBlock(ser)
print(data2)

