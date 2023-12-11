#include "Galapagos/Core/Component.hpp"

Component::Component(GameObject &associated) : m_associated(associated) {}

Component::~Component() {}

void Component::NotifyCollision(GameObject &other) {}

void Component::Start() {}