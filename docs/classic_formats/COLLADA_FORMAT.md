## 1. Общая структура COLLADA (.dae)

Файл `.dae` — это **XML-документ**. Основные блоки:

* `<asset>` — метаданные (единицы измерения, автор, координатная система).
* `<library_geometries>` — хранит геометрию (меши, полигоны, нормали, UV).
* `<library_images>` — ссылки на текстуры (обычно PNG, JPG, TIFF).
* `<library_materials>` — материалы, ссылаются на шейдеры и текстуры.
* `<library_effects>` — описывает визуальные эффекты (шейдеры, параметры освещения).
* `<library_visual_scenes>` — сцена: иерархия объектов, камер, источников света.
* `<library_cameras>` — параметры камер (перспективная/ортографическая, FOV, aspect ratio).
* `<library_lights>` — источники света.
* `<library_animations>` — анимации (ключи, кривые, таймлайны).
* `<library_controllers>` — скелетная анимация (skin, bones).
* `<scene>` — ссылка на основную сцену (`visual_scene`).

---

## 2. Что можно хранить для сферического контента

Чтобы адаптировать `.dae` под **сферический/360° проект**, обычно используют такие элементы:

* **Сферический меш (SkyDome/SkySphere):**

  * В `library_geometries` создаётся сфера.
  * На UV-развёртку натягивается equirectangular-текстура (`library_images`).

* **HDRI или панорама:**

  * Текстура подключается через `library_effects → profile_COMMON → technique → phong → diffuse/ambient`.

* **Камеры для VR:**

  * В `library_cameras` можно задать параметры камеры (угол обзора до 180°).
  * В `visual_scene` можно расположить камеру в центре сферы.

* **Анимации (переходы между панорамами, вращения):**

  * В `library_animations` можно хранить вращение камеры вокруг оси или fade-ин/аут панорамы.

* **Аудио (опционально):**

  * COLLADA **не поддерживает напрямую звук**, но можно расширить `<extra>` тегами.
  * Некоторые движки (например, X3D/GlTF) разрешают такие расширения.

---

## 3. Пример минимального `.dae` со сферой и камерой

```xml
<COLLADA xmlns="http://www.collada.org/2005/11/COLLADASchema" version="1.4.1">
  <asset>
    <unit name="meter" meter="1"/>
    <up_axis>Z_UP</up_axis>
  </asset>

  <library_images>
    <image id="sphere_tex" name="SphereTexture">
      <init_from>panorama_360.jpg</init_from>
    </image>
  </library_images>

  <library_materials>
    <material id="mat_sphere" name="SphereMaterial">
      <instance_effect url="#effect_sphere"/>
    </material>
  </library_materials>

  <library_effects>
    <effect id="effect_sphere">
      <profile_COMMON>
        <technique sid="common">
          <phong>
            <diffuse>
              <texture texture="sphere_tex" texcoord="UVSET0"/>
            </diffuse>
          </phong>
        </technique>
      </profile_COMMON>
    </effect>
  </library_effects>

  <library_geometries>
    <!-- Здесь описывается сфера (вершины, UV, нормали) -->
  </library_geometries>

  <library_cameras>
    <camera id="cam_360" name="MainCamera">
      <optics>
        <technique_common>
          <perspective>
            <yfov>180</yfov>
            <aspect_ratio>1.0</aspect_ratio>
            <znear>0.1</znear>
            <zfar>1000.0</zfar>
          </perspective>
        </technique_common>
      </optics>
    </camera>
  </library_cameras>

  <library_visual_scenes>
    <visual_scene id="Scene">
      <node id="SphereNode">
        <instance_geometry url="#sphere_geom">
          <bind_material>
            <technique_common>
              <instance_material symbol="mat_sphere" target="#mat_sphere"/>
            </technique_common>
          </bind_material>
        </instance_geometry>
      </node>
      <node id="CameraNode">
        <instance_camera url="#cam_360"/>
      </node>
    </visual_scene>
  </library_visual_scenes>

  <scene>
    <instance_visual_scene url="#Scene"/>
  </scene>
</COLLADA>
```
