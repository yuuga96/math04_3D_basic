#include"libOne.h"
//頂点位置の構造体
struct POS {
    float x, y, z;
};
//ゲームメイン
void gmain() {
    window(1000, 1000,full);
    //頂点の数
    int numCorners = 32;
    int numRings = numCorners / 2 + 1;
    const int numVertices = numCorners * numRings;
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
 //元の頂点位置（実行中も保持されている）
    struct POS* op = new POS[numVertices];
    for (int j = 0; j < numRings; j++) {
        float r = sin(deg * j);
        float z = cos(deg * j);
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(deg * i) * r;
            op[k].y = cos(deg * i) * r;
            op[k].z = z;// 1.0f - 2.0f / (numRings - 1) * j; //2を4で割る
        }
    }
    //変更後の頂点位置の入れ物（ループするたびに変化する）
    struct POS* p = new POS[numVertices];
    //元の頂点位置を回転させる角度
     deg = 0;
    angleMode(DEGREES);
    //このstateが0の時Y軸、1の時X軸回転する
    int state = 0;
    //メインループ
    while (notQuit) {
        //あらかじめsin,cosを計算しておく
        float s = sin(deg);
        float c = cos(deg);
        deg++;
        //stateの変更
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        //配列opの座標を変換して配列pに書き込む
        // ( 配列opの位置は変わらない )
        for (int i = 0; i < numVertices; i++) {
            //回転
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
            //奥に移動
            p[i].z += 5;
            //遠くの座標を小さくする
            p[i].x /= p[i].z;  //前後を表現するために短くする 
            p[i].y /= p[i].z;
        }
        //頂点位置を線で結び立方体にする
        clear(0);
        mathAxis(0.5);//クリア色と同じで軸は見えないが必要な命令
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




