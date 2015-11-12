/*
 *  Model Railroad Control Point codeline
 *  implemented on Particle's CoAP pub/sub event framework
 *
 *  John Plocher, 2015
 *
 */

#include "application.h"
#include "codeline-coap/codeline-coap.h"

codeline_coap::codeline_coap(char *layout) {
    strncpy (_layout, layout, sizeof(_layout) -1);
	_layout[sizeof(_layout) - 1] = '\0'; // force an ending null on overly long layout names
    sprintf(_control,   "ctc/%s/control", layout);
    sprintf(_indication,"ctc/%s/indication", layout);
    sprintf(_debug,     "debug/%s", layout);
}

int codeline_coap::CoAP2code(const char *event, const char *data,
			 char *layout, char *type, int *dst, int *src, int *code) {
	unsigned int meta;
	sscanf(event, "ctc/%s/%s", (char *)layout, (char *)type);
	sscanf(data,  "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", dst, src, &meta, 
		&code[0], &code[1], &code[2], &code[3], &code[4], &code[5], &code[6], &code[7]);
	return meta;
}

void codeline_coap::publish(int dst, int src, int meta, int *code) {
	if ((src == 0x69) || (src == 0x68)) {
		publishControls(dst, src, meta, code);
	} else {
		publishIndications(dst, src, meta, code);
	}
}

void codeline_coap::publishControls(int dst, int src, int meta, int *controls) {
	sendCTC(_control,    dst, src, meta, controls);
}

void codeline_coap::publishIndications(int dst, int src, int meta, int *indications) {
	sendCTC(_indication, dst, src, meta, indications);
}

void codeline_coap::sendCTC(const char *event, int dst, int src, int meta, int *a) {
	char data[64];
	sprintf(data, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", dst, src, meta, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	Particle.publish(event, data, 60, PUBLIC);
}



