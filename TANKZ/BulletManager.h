class BulletManager
{
public:
    BulletManager();
    ~BulletManager();

    static BulletManager* CreateInstance();
    static BulletManager* GetInstance() { return sInstance; };
    void updateBullets(DWORD milliseconds);
    void checkCollision();

    void resetBullet(int player);

    void fireBullet(int player);

    void init();

private:
    //bool CollideField();
    void CollideArena(int bullet, int bulletX, int bulletY);

    static BulletManager* sInstance;

    float bulletPosX[6]; // 0 - 2 = Player 1 bullets, 3-5 = player 2 bullets
    float bulletPosY[6];
    float bulletVelocityX[6];
    float bulletVelocityY[6];
    float bulletBounces[6];
    float bulletActive[6];

    DWORD mLastUpdateTime[2] = { 1000, 1000 };
    DWORD mCurrentTime[2] = { 2000, 2000 };
    int numBounces = 3;

    bool mEnabled;
    float mRadius;

};



