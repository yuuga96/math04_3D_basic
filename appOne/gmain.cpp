#include"libOne.h"
//���_�ʒu�̍\����
struct POS {
    float x, y, z;
};
//�Q�[�����C��
void gmain() {
    window(1000, 1000,full);
    //���_�̐�
    int numCorners = 32;
    int numRings = numCorners / 2 + 1;
    const int numVertices = numCorners * numRings;
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
 //���̒��_�ʒu�i���s�����ێ�����Ă���j
    struct POS* op = new POS[numVertices];
    for (int j = 0; j < numRings; j++) {
        float r = sin(deg * j);
        float z = cos(deg * j);
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(deg * i) * r;
            op[k].y = cos(deg * i) * r;
            op[k].z = z;// 1.0f - 2.0f / (numRings - 1) * j; //2��4�Ŋ���
        }
    }
    //�ύX��̒��_�ʒu�̓��ꕨ�i���[�v���邽�тɕω�����j
    struct POS* p = new POS[numVertices];
    //���̒��_�ʒu����]������p�x
     deg = 0;
    angleMode(DEGREES);
    //����state��0�̎�Y���A1�̎�X����]����
    int state = 0;
    //���C�����[�v
    while (notQuit) {
        //���炩����sin,cos���v�Z���Ă���
        float s = sin(deg);
        float c = cos(deg);
        deg++;
        //state�̕ύX
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        //�z��op�̍��W��ϊ����Ĕz��p�ɏ�������
        // ( �z��op�̈ʒu�͕ς��Ȃ� )
        for (int i = 0; i < numVertices; i++) {
            //��]
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            else {
                p[i].x = op[i].x;
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            //���Ɉړ�
            p[i].z += 5;
            //�����̍��W������������
            p[i].x /= p[i].z;  //�O���\�����邽�߂ɒZ������ 
            p[i].y /= p[i].z;
        }
        //���_�ʒu����Ō��ї����̂ɂ���
        clear(0);
        mathAxis(0.5);//�N���A�F�Ɠ����Ŏ��͌����Ȃ����K�v�Ȗ���
        stroke(160, 200, 255);
        strokeWeight(6);
        for (int i = 0; i < numVertices; i++) {
            //mathPoint(p[i].x, p[i].y);
            int j = i + 1;
            if (j % numCorners == 0)j -= numCorners;
            strokeWeight(2);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            if (i < numVertices - numCorners) {
            j = i + numCorners;
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }


        }
    }
    delete[]op;
    delete[]p;
}



