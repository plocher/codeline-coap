#ifndef _CODELINE_COAP_H_
#define _CODELINE_COAP_H_


class codeline_coap {
public:
    codeline_coap(char *layout);

    int decode(const char *event, const char *data, char *layout, char *type, int *dst, int *src, int *code) {
        return CoAP2code(event, data, layout, type, dst, src, code);
    }
    int CoAP2code(const char *event, const char *data, char *layout, char *type, int *dst, int *src, int *code);
    void publish           (int dst, int src, int meta, int *code);
    void publishControls   (int dst, int src, int meta, int *controls);
    void publishIndications(int dst, int src, int meta, int *indications);

    const char *layout()     { return _layout; }
    const char *control()    { return _control; }
    const char *indication() { return _indication; }
    const char *debug()      { return _debug; }

private:
    void sendCTC(const char *event, int dst, int src, int meta, int *a);

    char _layout    [10];
    char _control   [sizeof("ctc/") + sizeof(_layout) + sizeof("/control")];
    char _indication[sizeof("ctc/") + sizeof(_layout) + sizeof("/indication")];
    char _debug     [sizeof("debug/") + sizeof(_layout)];
};

#endif

