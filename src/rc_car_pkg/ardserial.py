import serial
def getData(port:str,counter:int,rate:int = 57600,):
    '''Use this function to get the data from the serial port
    @port - Whichport to read serial info from, example COM5
    @counter - How many angles or datapoints you need
    @rate - Baudrate at which the data is being sent to the serial port, default is 57600'''
    arduino = serial.Serial(port=port,baudrate=rate)
    distances = []
    angles=[]
    strengths = []

    while True:
        data = arduino.readline()
        data = data.decode()
        splits = data.split('\t')
        angle = splits[-1].split(' ')[-1]
        angle = int(angle)
        dist = splits[0].split(' ')
        strength = float((splits[1].split(' '))[-1])
        distances.append(float(dist[-1]))
        angles.append(angle)
        strengths.append(strength)
        counter-=1
        print(f'{counter} iters left\t',end='\r')
        if counter<=0:
            break
    return distances,angles,strengths





