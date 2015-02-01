#include "include/main.hpp"
#include "include/RayTracing.hpp"

// For every pixel we paint, we need to ray trace
// it correctly.
RT_Vec3 put_pixel(int i, int j)
{
    double left_bottom_x = -VIEW_WIDTH / 2.0 + \
        PIXEL_WIDTH * i;
    double left_bottom_y = -VIEW_HEIGHT / 2.0 + \
        PIXEL_HEIGHT * j;
    RT_Vec3 pixel,direction,resultColor;
    Ray ray;
    pixel = RT_Vec3(left_bottom_x, left_bottom_y, SCREEN_Z);
    direction = pixel - cam_position;
    ray = Ray(cam_position, direction);
    resultColor += ray_trace(ray, TRACE_DEPTH);
    
    return resultColor;
}

// This function gets the cube and cylinder shapes.
void shape_retrieve(RT_Shape* curr_shape, const char* file_path, \
    int size, int vert_size, int face_size, RT_Vec3 loc)
{
    FILE* data = fopen(file_path, "r");
    if (!data)
    {
        cerr << "Cannot find " << file_path << endl;
        exit(1);
    }
    
    double vert_x, vert_y, vert_z;
    for (int i = 0; i < vert_size; i++)
    {
        fscanf(data,"%lf %lf %lf", &vert_x, &vert_y, &vert_z);
        vert_x *= size;
        vert_y *= size;
        vert_z *= size;
        curr_shape->vertices.push_back(RT_Vec3(vert_x, vert_y, vert_z) + \
            loc);
    }

    int temp, pt1, pt2, pt3;
    for (int i = 0; i < face_size; i++)
    {
        fscanf(data,"%d %d %d %d", &temp, &pt1, &pt2, &pt3);
        curr_shape->indices.push_back(pt1);
        curr_shape->indices.push_back(pt2);
        curr_shape->indices.push_back(pt3);
    }

    fclose(data);
    curr_shape->calSurround();
}

// This paints the canvas with the correct number of objects
// as specified.
void draw_objects()
{
    RT_Object *curr_obj;

    if (multiple_object)
    {
        // Red sphere
        curr_obj = new RT_Sphere(RT_Vec3(2.0f, -5.0f, 55.0f), 5.0f);
        curr_obj->setKa(RT_Vec3(0.5f, 0.0f, 0.0f));
        curr_obj->setKd(RT_Vec3(0.3f, 0.3f, 0.3f));
        curr_obj->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        curr_obj->setShininess(30.0f);
        curr_obj->setReflectivity(0.4f);
        curr_obj->setTransparency(0.0f);
        object_list.push_back(curr_obj);

        // Gray sphere
        curr_obj=new RT_Sphere(RT_Vec3(-25.0f, 0.0f, 3.0f), 6.0f);
        curr_obj->setKa(RT_Vec3(0.3f, 0.3f, 0.3f));
        curr_obj->setKd(RT_Vec3(0.3f, 0.3f, 0.3f));
        curr_obj->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        curr_obj->setShininess(50.0f);
        curr_obj->setReflectivity(0.5f);
        curr_obj->setTransparency(0.0f);
        object_list.push_back(curr_obj);

        // Yellow sphere
        curr_obj=new RT_Sphere(RT_Vec3(10.0f, 5.0f, 2.0f), 6.0f);
        curr_obj->setKa(RT_Vec3(0.5f, 0.5f, 0.0f));
        curr_obj->setKd(RT_Vec3(0.3f, 0.3f, 0.3f));
        curr_obj->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        curr_obj->setShininess(70.0f);
        curr_obj->setReflectivity(0.5f);
        curr_obj->setTransparency(0.0f);
        object_list.push_back(curr_obj);

        // Cyan cylinder
        RT_Shape* cylinder = new RT_Shape();
        shape_retrieve(cylinder, "include/cylinder.data", \
            5, 34, 64, RT_Vec3(25.0f, -2.0f, 30.0f));
        cylinder->setKa(RT_Vec3(0.5f, 0.0f, 0.5f));
        cylinder->setKd(RT_Vec3(0.3f, 0.3f, 0.3f));
        cylinder->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        cylinder->setShininess(20.0f);
        cylinder->setReflectivity(0.5f);
        cylinder->setTransparency(0.0f);
        object_list.push_back(cylinder);

        // Green cube
        RT_Shape* cube = new RT_Shape();
        shape_retrieve(cube, "include/cube.data", \
            3, 8, 12, RT_Vec3(-15.0f, -5.0f, 50.0f));
        cube->setKa(RT_Vec3(0.0f, 0.8f, 0.0f));
        cube->setKd(RT_Vec3(0.3f, 0.3f, 0.3f));
        cube->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        cube->setShininess(30.0f);
        cube->setReflectivity(0.8f);
        cube->setTransparency(0.0f);
        object_list.push_back(cube);
    }

    else
    {
        // Purple transparent sphere
        curr_obj = new RT_Sphere(RT_Vec3(-2.0f, 0.4f, 15.0f), 10.0f);
        curr_obj->setKa(RT_Vec3(0.4f, 0.0f, 0.4f));
        curr_obj->setKd(RT_Vec3(0.3f, 0.3f, 0.3f));
        curr_obj->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        curr_obj->setShininess(30.0f);
        curr_obj->setReflectivity(0.0f);
        curr_obj->setTransparency(0.7f);
        object_list.push_back(curr_obj);
    }

    // Gray/white floor
    curr_obj = new RT_Floor(RT_Vec3(0.0f, 1.0f, 0.0f), \
        RT_Vec3(0.0f, -10.0f, 0.0f));
    curr_obj->setKa(RT_Vec3(0.8f, 1.0f, 0.8f));
    curr_obj->setKd(RT_Vec3(0.0f, 0.2f, 0.4f));
    curr_obj->setKs(RT_Vec3(0.3f, 0.0f, 0.0f));
    curr_obj->setShininess(0.0f);
    curr_obj->setReflectivity(0.7f);
    curr_obj->setTransparency(0.0f);
    object_list.push_back(curr_obj);
}

// This adds light to the canvas as specified.
void light_source()
{
    PointLight* pl = new PointLight();
    if (multiple_light)
    {
        // Two lights from above.
        pl->setPosition(RT_Vec3(5.0f, 15.0f, 20.0f));
        pl->setKa(RT_Vec3(1.0f, 1.0f, 1.0f));
        pl->setKd(RT_Vec3(0.0f, 0.0f, 1.0f));
        pl->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        light_list.push_back(pl);

        pl = new PointLight();
        pl->setPosition(RT_Vec3(-5.0f, 50.0f, -20.0f));
        pl->setKa(RT_Vec3(0.5f, 0.5f, 0.5f));
        pl->setKd(RT_Vec3(0.5f, 0.5f, 0.5f));
        pl->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        light_list.push_back(pl);
    }

    else
    {
        // One light at eye sight.
        pl->setPosition(RT_Vec3(0.0f, 15.0f, 90.0f));
        pl->setKa(RT_Vec3(1.0f, 1.0f, 1.0f));
        pl->setKd(RT_Vec3(0.0f, 0.0f, 1.0f));
        pl->setKs(RT_Vec3(1.0f, 1.0f, 1.0f));
        light_list.push_back(pl);
    } 
}

// This is the OpenGL init function.
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDepthFunc(GL_LEQUAL);

    draw_objects();
    light_source();
}

// This is the progress bar printed out
// in the terminal.
void print_progress(int curr_step)
{
    if (real_try == 1)
        curr_step += 20;
    int display_width = 40;
    cout << "[";
    int pos = curr_step;
    
    for (int i = 0; i < display_width; i++)
    {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(curr_step * 2.5) << " %\r";
    cout.flush();
}

// OpenGL display function. This also calls the progress
// bar function.
void display()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glBegin(GL_POINTS);
    progress = 0;
    real_try++;
    if (real_try == 0)
    {
        cout << "Painting in Progress..." << endl;
    }

    int currentInt;
    for (int i = 0; i < IMAGE_WIDTH; i++)
    {
        for (int j = 0; j < IMAGE_HEIGHT; j++)
        {
            currentInt = (i * IMAGE_HEIGHT + j + 1) * \
                20 / (IMAGE_WIDTH * IMAGE_HEIGHT);
            if (currentInt > progress)
            {
                progress = currentInt;
                print_progress(currentInt);
            }
            RT_Vec3 resultColor = put_pixel(i, j);
            glColor3f(resultColor.x, resultColor.y, resultColor.z);
            glVertex3f(i, j, 0);
        }
    }
    glEnd();
    glutSwapBuffers();
}

// OpenGL reshape function.
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, IMAGE_WIDTH, 0, IMAGE_HEIGHT);
}

// This handles the arguments input by user.
void parse_argument(int argc, char **argv)
{
    if (cmd_option_exists(argv, argv + argc, "-help") || \
        cmd_option_exists(argv, argv + argc, "-h"))
    {
        usage(argv[0]);
        exit(1);
    }

    // This is to adjust the view point.
    if (cmd_option_exists(argv, argv + argc, "-v"))
    {
        char view_angle = get_cmd_option(argv, argv + argc, "-v")[0];
        if (view_angle == 'l')
            cam_position.x = -20.0f;
        else if (view_angle == 'c')
            cam_position.x = 0.0f;
        else if (view_angle == 'r')
            cam_position.x = 20.0f;
        else
        {
            cerr << "Invalid camera position!" << endl;
            usage(argv[0]);
            exit(1);
        }
    }

    // This is to select the number of objects.
    if (cmd_option_exists(argv, argv + argc, "-o"))
    {
        char view_angle = get_cmd_option(argv, argv + argc, "-o")[0];
        if (view_angle == 's')
            multiple_object = false;
        else if (view_angle == 'm')
            multiple_object = true;
        else
        {
            cerr << "Invalid num of objects!" << endl;
            usage(argv[0]);
            exit(1);
        }
    }

    // This is to adjust the number of light source.
    if (cmd_option_exists(argv, argv + argc, "-l"))
    {
        char view_angle = get_cmd_option(argv, argv + argc, "-l")[0];
        if (view_angle == 's')
            multiple_light = false;
        else if (view_angle == 'm')
            multiple_light = true;
        else
        {
            cerr << "Invalid num of light source!" << endl;
            usage(argv[0]);
            exit(1);
        }
    }
}

int main(int argc, char **argv)
{
    parse_argument(argc, argv);

    // OpenGL functions
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB \
        | GLUT_MULTISAMPLE);
    glutInitWindowSize (IMAGE_WIDTH, IMAGE_HEIGHT); 
    glutInitWindowPosition (300, 100);
    glutCreateWindow ("CS 171 HW 6 and 7");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
