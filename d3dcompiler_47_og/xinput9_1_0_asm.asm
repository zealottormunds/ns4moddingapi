.code
extern mProcs:QWORD
DllMain_wrapper proc
	jmp mProcs[0*8]
DllMain_wrapper endp
XInputGetCapabilities_wrapper proc
	jmp mProcs[1*8]
XInputGetCapabilities_wrapper endp
XInputGetDSoundAudioDeviceGuids_wrapper proc
	jmp mProcs[2*8]
XInputGetDSoundAudioDeviceGuids_wrapper endp
XInputGetState_wrapper proc
	jmp mProcs[3*8]
XInputGetState_wrapper endp
XInputSetState_wrapper proc
	jmp mProcs[4*8]
XInputSetState_wrapper endp
end
