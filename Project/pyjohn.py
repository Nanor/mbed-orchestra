import serial, time, wave, struct

def getWav(filename):
	wav = wave.open(("Samples/"+filename), 'r')
	data = []

	length = wav.getnframes()
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
	

def int2bin(d):
	a = d >> 8
	b = d % (2 ** 9)
	out = [a,b]
	for i in range(2):
		if out[i] == 0:
			out[i] = 255
	
	return out


def sendData(data, ser):
	length = len(data)
	lengthArray = int2bin(length)
	
	print("Sending Length")
	for i in lengthArray:
		print("sending", i)
		ser.write(chr(i))
		
	for i in range(2):
		inp = ser.read(1)
		print(ord(inp))
	
	print("Waiting for length confirmation")
	inp = ser.read(1)
	print(ord(inp))
	
	print("Sending data")
	for i in data:
		print("sending", i)
		ser.write(chr(i))
	
	print("Waiting for data confirmation")
	inp = ser.read(1)
	print(inp)
	
	print("Receiving data")
	for i in range(19):
		inp = ser.read(1)
		print("receiving", ord(inp))

	ser.close()

def readFor(n, ser, printChar):
	if n == -1:
		while(1):
			if printChar:
				print(ser.read(1))
			else:
				print(ord(ser.read(1)))
	for i in range(n):
		if printChar:
			print(ser.read(1))
		else:
			print(ord(ser.read(1)))
			
def write(wave):
	file1 = open("johnscoolwaveform.c", 'w')
	file1.write("#include \"lpc_types.h\" \n")
	file1.write("uint8_t johnscoolwaveform[] = \n")
	file1.write(str(wave).replace('[','{').replace(']', '}')+';')
	
	file1.close()

wave = getWav("piano.wav")
print(len(wave))
write(wave)
#ser = serial.Serial("/dev/ttyACM1")
#readFor(-1, ser, 0)
#sendData(range(1, 20), ser)



