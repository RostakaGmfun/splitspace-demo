#include <splitspace/Engine.hpp>
#include <splitspace/Config.hpp>
#include <splitspace/EventManager.hpp>
#include <splitspace/ResourceManager.hpp>
#include <splitspace/RenderManager.hpp>
#include <splitspace/Scene.hpp>
#include <splitspace/Camera.hpp>
#include <splitspace/Entity.hpp>
#include <splitspace/Light.hpp>
#include <splitspace/RenderTechnique.hpp>
#include <splitspace/ForwardRenderTechnique.hpp>
#include <splitspace/DefferedRenderTechnique.hpp>

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace splitspace;

class Demo: public EventListener {
public:
    Demo(): EventListener(EVM_WINDOW|EVM_INPUT|EVM_GAME, "MyListener"),
                  m_engine(nullptr), m_scene(nullptr)
    {}

    int run() {
        m_engine = new Engine();
        if(!m_engine->init()) {
            return 1;
        }

        m_renderTechnique = new DefferedRenderTechnique(m_engine);

        if(!m_renderTechnique->init()) {
            return 1;
        }

        m_scene = static_cast<Scene *>(m_engine->resManager->loadResource("demoScene"));
        if(!m_scene) {
            return 1;
        }

        m_renderTechnique->setScene(m_scene);

        m_camera = new LookatCamera(m_engine->config->window.width,
                                 m_engine->config->window.height,
                                 45.f, 1.0f, 1000.f);
        m_camera->setPosition(glm::vec3(0, 0, 5));
        const auto &objects = m_scene->getRootNode()->getChildren();
        const auto &cart= std::find_if(objects.begin(), objects.end(),
                              [](Entity *e) {
                                return e->getName() == "cart";
                              });

        const auto &pointLight = std::find_if(objects.begin(), objects.end(),
                              [](Entity *e) {
                                return e->getName() == "PointLight";
                              });

        const auto &dirLight = std::find_if(objects.begin(), objects.end(),
                              [](Entity *e) {
                                return e->getName() == "DirectionalLight";
                              });


        if(pointLight == objects.end() ||
           dirLight == objects.end()) {
            return 1;
        }

        m_pointLight = static_cast<Light*>(*pointLight);
        m_dirLight = static_cast<Light*>(*dirLight);
        m_camera->setLookPosition((*cart)->getPos());

        m_renderTechnique->setViewCamera(m_camera);

        m_engine->renderManager->setCamera(m_camera);
        m_engine->renderManager->setScene(m_scene);
        m_engine->renderManager->setRenderTechnique(m_renderTechnique);
        m_engine->eventManager->addListener(this);
        m_engine->mainLoop();

        delete m_camera;
        return 0;
    }

    virtual void onEvent(Event *e) {
        switch(e->type) {
            case EV_QUIT:
                m_engine->shutdown();
            break;
            case EV_KEY:
                handleKey(static_cast<KeyboardEvent *>(e));
            break;
            case EV_MOUSE:
                handleMouse(static_cast<MouseEvent *>(e));
            break;
            case EV_UPDATE:
                handleUpdate(static_cast<UpdateEvent *>(e));
            break;
            default:
            break;
        }
    }

private:
    void handleKey(const KeyboardEvent *kbev) {
        static_cast<void>(kbev);
    }

    void handleMouse(const MouseEvent *mev) {
        static_cast<void>(mev);
    }

    void handleUpdate(const UpdateEvent *uev) {
        using namespace std::chrono;
        static int t = 1;
        const float radius = 1.5f;
        float red = std::fabs(std::sin(t/50.f));
        float blue = std::fabs(std::cos(t/50.f));
        m_pointLight->setDiffuse(glm::vec3(red, blue, 1-red));
        const auto &pos = m_pointLight->getPos();
        m_pointLight->setPos(glm::vec3(std::sin(t/50.f)*radius,
                             pos.y, std::cos(t/50.f)*radius));
        m_camera->update(uev->delta);
        m_scene->update(uev->delta);
        t++;
    }

private:
    Engine *m_engine;
    Scene *m_scene;
    LookatCamera *m_camera;
    Light *m_pointLight;
    Light *m_dirLight;
    DefferedRenderTechnique *m_renderTechnique;
};

int main() {
    Demo d;
    return d.run();
}
