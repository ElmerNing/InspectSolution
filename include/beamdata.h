#ifndef beamdata_h__
#define beamdata_h__

class BeamData
{
public:
    BeamData();
    ~BeamData();

    enum some_const{
        BEAM_PONIT_DELT = 32,
    };

    void Init(uchar* data, int pointQty);
    uchar* Data() { return m_data; }
    int Len() { return m_len; }
    inline uchar operator[](int index) { return m_data[index]; }

private:
    uchar* m_data;
    int m_len;
};

#endif // beamdata_h__