.name			"ANTON MOROZIUK"
.comment		"The strongest champion created by pzakala, okryzhan, amoroziu and vlytvyne!"

xor		r2, r1, r1
st		r1, 6
loop:
	live %0
	fork %100
	ld %0, r10
	zjmp %:loop
