import serial, time, wave, struct

def getWav(filename):
	wav = wave.open(("Samples/"+filename), 'r')
	data = []
	
	length = wav.getnframes()
	for i in range(0,length):
		waveData = wav.readframes(1)
		data.append(struct.unpack("<h", waveData)[0])
		
	wav.close()
	
	normWave(data)
	print(data[0:8])
	
	return data
	
def normWave(data):
	maxVal = float(max(data))
	for i in range(len(data)):
		data[i] = int(((data[i]+maxVal)/(2*maxVal)) * 255)
		if data[i] == 0:
			data[i] += 1
		
def send8digits(ls):
	ser = serial.Serial("/dev/ttyACM0")

	data = []
	for i in ls:
		data.append(chr(i))

	print("Writing word")
	for i in data:
		ser.write(i)

	print("Reading word")
	inp = ser.read(8)
	out = []
	for i in inp:
		out.append(ord(i))
	print(out)

	ser.close()

wave = getWav("Beep1.wav")
print(len(wave))
send8digits(wave[0:8])
#print(wave[0:100])


