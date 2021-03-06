/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Math/PolygonPrism.h>

#include "PolygonPrismShape.h"
#include "Rendering/EntityDebugDisplayComponent.h"

namespace LmbrCentral
{
    /**
     * Component interface for Polygon Prism.
     * Formal Definition: A polygonal prism is a 3-dimensional prism made from two translated polygons connected by rectangles.
     * Here the representation is defined by one polygon (internally represented as a vertex container - list of vertices) and a height (extrusion) property.
     * All points lie on the local plane Z = 0.
     */
    class PolygonPrismShapeComponent
        : public AZ::Component
    {
    public:
        friend class EditorPolygonPrismShapeComponent;

        AZ_COMPONENT(PolygonPrismShapeComponent, "{AD882674-1D5D-4E40-B079-449B47D2492C}");

        PolygonPrismShapeComponent() = default;

        // AZ::Component
        void Activate() override;
        void Deactivate() override;

    protected:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
        {
            provided.push_back(AZ_CRC("ShapeService", 0xe86aa5fe));
            provided.push_back(AZ_CRC("PolygonPrismShapeService", 0x1cbc4ed4));
            provided.push_back(AZ_CRC("VertexContainerService", 0x22cf8e10));
        }

        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
        {
            incompatible.push_back(AZ_CRC("ShapeService", 0xe86aa5fe));
            incompatible.push_back(AZ_CRC("PolygonPrismShapeService", 0x1cbc4ed4));
            incompatible.push_back(AZ_CRC("VertexContainerService", 0x22cf8e10));
        }

        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
        {
            required.push_back(AZ_CRC("TransformService", 0x8ee22c50));
        }

        static void Reflect(AZ::ReflectContext* context);

    private:
        PolygonPrismShape m_polygonPrismShape; ///< Stores configuration of a Polygon Prism Shape for this component
    };

    /**
     * Concrete EntityDebugDisplay implementation for PolygonPrismShape.
     */
    class PolygonPrismShapeDebugDisplayComponent
        : public EntityDebugDisplayComponent
    {
    public:
        AZ_COMPONENT(PolygonPrismShapeDebugDisplayComponent, "{FBDABBAB-F754-4637-BF26-9AB89F3AF626}")

        PolygonPrismShapeDebugDisplayComponent() = default;
        explicit PolygonPrismShapeDebugDisplayComponent(const AZ::PolygonPrism& polygonPrism)
            : m_polygonPrism(polygonPrism) {}

        // AZ::Component
        void Activate();

        static void Reflect(AZ::ReflectContext* context);

        void Draw(AzFramework::EntityDebugDisplayRequests* displayContext) override;

    private:
        AZ_DISABLE_COPY_MOVE(PolygonPrismShapeDebugDisplayComponent)

        // AZ::TransformNotificationBus::Handler
        void OnTransformChanged(const AZ::Transform& local, const AZ::Transform& world) override;

        void GenerateVertices();

        AZ::PolygonPrism m_polygonPrism; ///< Stores configuration data for PolygonPrism shape.
        PolygonPrismMesh m_polygonPrismMesh; ///< Buffer to store triangles of top and bottom of Polygon Prism.
    };
} // namespace LmbrCentral