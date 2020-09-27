#include <fireworks/fireworks.h>
#include <box2d/box2d.h>

using namespace fireworks;

#define M2P 5
#define P2M 1/M2P

class FreeFall : public Fireworks
{
private:
    Window*         m_Window;
    Layer*          m_DefaultLayer;

    b2Vec2          m_Gravity;
    const double    m_PhysicsTimeStep = 1.0f / 60.0f;
    unsigned int    m_VelocityIterations;
    unsigned int    m_PositionIterations;
public:
    b2World*        world;

    b2BodyDef       groundBodyDef;
    b2Body*         groundBody;
    b2PolygonShape  groundShape;
    b2FixtureDef    groundFixtureDef;

    b2BodyDef       dynBoxBodyDef;
    b2Body*         dynBoxBody;
    b2PolygonShape  dynBoxShape;
    b2FixtureDef    dynBoxFixtureDef;

    Sprite*         ground;
    Sprite*         dynBox;
    Texture*        snakeTex;
public:
    FreeFall()
        : m_Gravity(b2Vec2(0.0f, -9.81f)), m_VelocityIterations(6), m_PositionIterations(2)
    {
        world = new b2World(m_Gravity);

        // Static ground body
        groundBodyDef.position.Set(-2.0f * P2M, -4.0f * P2M);
        groundBody = world->CreateBody(&groundBodyDef);
        groundShape.SetAsBox(5.0f * P2M, 2.0f * P2M);
        groundFixtureDef.shape = &groundShape;
        groundFixtureDef.density = 1.0f;
        groundFixtureDef.friction = 0.3f;
        groundBody->CreateFixture(&groundFixtureDef);

        // Dynamic simulation box
        dynBoxBodyDef.type = b2_dynamicBody;
        dynBoxBodyDef.position.Set(0.0f * P2M, 4.0f * P2M);
        dynBoxBody = world->CreateBody(&dynBoxBodyDef);
        dynBoxShape.SetAsBox(1.0f * P2M, 1.0f * P2M);
        dynBoxFixtureDef.shape = &dynBoxShape;
        dynBoxFixtureDef.density = 1.0f;
        dynBoxFixtureDef.friction = 0.25f;
        dynBoxBody->CreateFixture(&dynBoxFixtureDef);
    }

    ~FreeFall()
    {
        delete m_DefaultLayer;
        delete world;
    }

    // Runs once per initialisation
    void init() override
    {
        m_Window = createWindow("Freefall physics sim", 800, 600);
        glClearColor(0.8, 0.8f, 0.2f, 1.0f);

        m_DefaultLayer = new Layer(new BatchRenderer2D(),
                                new Shader( "../Fireworks-core/src/shaders/basic.vert",
                                            "../Fireworks-core/src/shaders/basic.frag"),
                                mat4::orthographic(-8.0f, 8.0f, -6.0f, 6.0f, -1.0f , 1.0f));

        snakeTex = new Texture("../Resources/fireworks.png");
        dynBox   = new Sprite(dynBoxBody->GetPosition().x, dynBoxBody->GetPosition().y, 0.1f * M2P, 0.1f * M2P, snakeTex);
        ground   = new Sprite(groundBody->GetPosition().x * M2P, groundBody->GetPosition().y * M2P, 0.5f * M2P, 0.2f * M2P, vec4(0.3f, 0.0f, 0.1f, 1.0f));

        m_DefaultLayer->add(ground);
        m_DefaultLayer->add(dynBox);
    }

    // Runs once per second
    void tick() override { }

    // Runs 60 times per second
    void update() override
    {
        //Physics Update
        world->Step(m_PhysicsTimeStep, m_VelocityIterations, m_PositionIterations);
        b2Vec2 dynPos = dynBoxBody->GetPosition();
        b2Vec2 dynCenter = dynBoxBody->GetWorldCenter();

        dynBox->position = vec3(dynPos.x * M2P, dynPos.y * M2P, 0.0f);
    }

    // Runs as fast as possible
    void render() override
    {
        glEnable(GL_BLEND);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_DefaultLayer->render();
    }
};
