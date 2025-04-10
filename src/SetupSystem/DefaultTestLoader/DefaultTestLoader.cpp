#include "DefaultTestLoader.h"

void load_default_test(ParticleBuilder *particle_builder, int test_id)
{
    switch (test_id)
    {
    case (0):
        particle_builder->legacy_spawn_globular_cluster(500, glm::vec3(-550, -700, 0), 200, 25, 1000, 100000, 10, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(500, glm::vec3(470, 650, 0), 200, 25, 1000, 100000, 10, 1000, false, false);
        break;

    case (1):
        particle_builder->legacy_spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 200, 25, 1000, 100000, -1000, 1000, false, false);
        break;

    case (2):
        particle_builder->legacy_spawn_sphere(1000, glm::vec3(0, 0, 0), 750, 1000, 100000, -1000, 1000, false);
        break;

    case (3):
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(0, 0, 0), 500, 50, 1000, 100000, 0, 0, false);
        break;

    case (4):
        particle_builder->legacy_spawn_random(100, glm::vec3(0.0f), 500, 1000, 100000, 0, 1000);
        break;

    case (5):
        particle_builder->legacy_spawn_double_sphere(10000, glm::vec3(0, 0, 0), 700, 50, 1000, 100000, -1000, 1000, false);
        break;

    case (6):
        particle_builder->legacy_spawn_double_sphere(9999, glm::vec3(0, 0, 0), 10000, 50, 1000, 100000, -100, 100, false);
        break;

    case (7):
        particle_builder->legacy_spawn_double_sphere(10000, glm::vec3(0, 0, 0), 100000, 50, 1000, 100000, -100, 100, false);
        break;

    case (8):
        particle_builder->legacy_spawn_globular_cluster(10000, glm::vec3(0, 0, 0), 50000, 50, 1000, 100000, -10000, 10000, false, false);
        break;

    case (9):
        particle_builder->legacy_spawn_globular_cluster(5000, glm::vec3(-550, -600, 0), 200, 25, 1000, 100000, 10, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(5000, glm::vec3(470, 450, 0), 200, 25, 1000, 100000, 10, 1000, false, false);
        break;

    case (10):
        particle_builder->legacy_spawn_double_sphere(2500, glm::vec3(-550, -600, 0), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(2500, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(2500, glm::vec3(124, -2634, -156), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(2500, glm::vec3(-470, 440, -48), 10000, 25, 1000, 100000, 10, 1000, false);
        break;

    case (11):
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(-550, -600, 0), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(124, -2634, -156), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(-470, 440, -48), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(1470, 3440, -4238), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(-470, 41243, 248), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(-470, 150, -48), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(3170, 49, 4488), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(570, 330, -48), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(0, 0, 0), 10000, 25, 1000, 100000, 10, 1000, false);
        break;

    case (12):
        particle_builder->legacy_spawn_double_sphere(1500, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, -1000, 1000, false);
        particle_builder->legacy_spawn_double_sphere(800, glm::vec3(-550, -600, 0), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(800, glm::vec3(124, -2634, -156), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(-470, 440, -48), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(1470, 3440, -4238), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(-470, 41243, 248), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(-470, 150, -48), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(600, glm::vec3(3170, 49, 4488), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(100, glm::vec3(570, 330, -48), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(200, glm::vec3(0, 0, 0), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(200, glm::vec3(250, -600, 887), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(200, glm::vec3(828, -2634, -827), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(200, glm::vec3(-8272, 551, -254), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(200, glm::vec3(52, 8, -4238), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(200, glm::vec3(-85, 5452, 248), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(-425, 1550, -28), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(340, 45, 52), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(5702, 330, -548), 10000, 25, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(500, glm::vec3(5, 50, 750), 10000, 25, 1000, 100000, 10, 1000, false);
        break;

    case (13):
        particle_builder->legacy_spawn_sphere(9000, glm::vec3(0, 0, 0), 10000, 1000, 100000, 10, 1000, false);
        particle_builder->legacy_spawn_double_sphere(1000, glm::vec3(0, 0, 0), 500, 25, 100000, 10000000, 10, 1000, false);
        break;

    case (14):
        particle_builder->legacy_spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 10000, 25, 1000, 10000, 10, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(0, 0, 0), 1, 0, 10000000, 10000000, 0, 0, false, false);
        break;

    case (15):
        particle_builder->legacy_spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 100, 1000, 10000, 100000, 10000, 100000, true, false);
        particle_builder->legacy_spawn_sphere(1, glm::vec3(0, 0, 0), 1, 10000000, 10000000, 10000, 10000, true);
        break;

    case (16):
        particle_builder->legacy_spawn_sphere(20000, glm::vec3(0, 0, 0), 35, 0, 0, -1000, 1000, false);
        particle_builder->legacy_spawn_globular_cluster(200, glm::vec3(5000, 5000, 5000), 1, 0, 10000000, 10000000, -1000, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(200, glm::vec3(-5000, -5000, -5000), 1, 0, 10000000, 10000000, -1000, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(200, glm::vec3(-5000, 5000, -5000), 1, 0, 10000000, 10000000, -1000, 1000, false, false);
        break;

    case (17):
        particle_builder->legacy_spawn_sphere(20000, glm::vec3(0, 0, 0), 35, 1, 1, -1000, 1000, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, 5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, 5000, -5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, -5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-5000, 5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-5000, -5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, -5000, -5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-5000, -5000, -5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false);
        break;

    case (18):
        particle_builder->legacy_spawn_sphere(20000, glm::vec3(0, 0, 0), 15, 1, 1, -1000, 1000, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, 5000, 5000), 10000, 0, 1000000000, 1000000000, -10000, -10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, 5000, -5000), 10000, 0, 1000000000, 1000000000, -10000, -10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, -5000, 5000), 10000, 0, 1000000000, 1000000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-5000, 5000, 5000), 10000, 0, 1000000000, 1000000000, -10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-5000, -5000, 5000), 10000, 0, 1000000000, 1000000000, 10000, -10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(5000, -5000, -5000), 10000, 0, 1000000000, 1000000000, 10000, -10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-5000, 5000, -5000), 10000, 0, 1000000000, 1000000000, 10000, 10000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-5000, -5000, -5000), 10000, 0, 1000000000, 1000000000, 10000, 10000, false, false);
        break;

    case (19):
        particle_builder->legacy_spawn_globular_cluster(10000, glm::vec3(1000, 0, 0), 1000, 10000, 1, 1, 1000, 10000, true, false);
        particle_builder->legacy_spawn_globular_cluster(10000, glm::vec3(-1000, 0, 0), 1000, 10000, 1, 1, 1000, 10000, true, false);
        particle_builder->legacy_spawn_sphere(100, glm::vec3(0, 0, 0), 1, 10000000, 10000000, 0, 0, true);
        break;

    case (20):
        particle_builder->legacy_spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 1000, 10000, 100000, 1000000, 10000, 100000, true, false);
        particle_builder->legacy_spawn_sphere(1, glm::vec3(0, 0, 0), 1, 10000000, 10000000, 0, 0, true);
        break;

    case (21):
        particle_builder->legacy_spawn_sphere(7000, glm::vec3(10000, 0, 0), 10, 10000000, 10000000, 0, 0, false);
        particle_builder->legacy_spawn_sphere(7000, glm::vec3(0, 10000, 0), 10, 10000000, 10000000, 0, 0, false);
        particle_builder->legacy_spawn_sphere(7000, glm::vec3(-10000, 0, 0), 10, 10000000, 10000000, 0, 0, false);
        particle_builder->legacy_spawn_sphere(7000, glm::vec3(0, -10000, 0), 10, 10000000, 10000000, 0, 0, false);
        break;

    case (22):
        particle_builder->legacy_spawn_sphere(29999, glm::vec3(0, 0, 0), 35, 0, 0, -1000, 1000, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(500, 500, 500), 1, 0, 10000000, 10000000, -1000, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-500, 500, 500), 1, 0, 10000000, 10000000, -1000, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(-500, -500, -500), 1, 0, 10000000, 10000000, -1000, 1000, false, false);
        particle_builder->legacy_spawn_globular_cluster(1, glm::vec3(500, -500, -500), 1, 0, 10000000, 10000000, -1000, 1000, false, false);
        break;

    case (23):
        particle_builder->legacy_spawn_sphere(1, glm::vec3(0, 0, 0), 4, 100000000, 100000000, 0, 0, false);
        particle_builder->legacy_spawn_sphere(40000, glm::vec3(0, 0, 0), 4, 1000000, 1000000, 0, 0, false);
        break;

    case (24):
        particle_builder->legacy_spawn_disc(20000, glm::vec3(-10000, 0, 0), 1000, 20, 100000, 1000000, 10000, 100000, true, false);
        particle_builder->legacy_spawn_sphere(1, glm::vec3(-10000, 0, 0), 1, 1000000, 1000000, 0, 0, true);

        particle_builder->legacy_spawn_disc(20000, glm::vec3(10000, 0, 0), 1000, 20, 100000, 1000000, 10000, 100000, true, false);
        particle_builder->legacy_spawn_sphere(1, glm::vec3(10000, 0, 0), 1, 1000000, 1000000, 0, 0, true);
        break;

    case 25:
        particle_builder->legacy_spawn_disc(20000, glm::vec3(0, 0, 0), 1000, 20, 10000, 100000, 5000, 50000, 1, false);
        particle_builder->legacy_spawn_random(1000, glm::vec3(999, 999, 999), 1000, 50, 50, 50, 50);
        particle_builder->legacy_spawn_double_sphere(10000, glm::vec3(0, 0, 0), 10000, 10, 1000000, 10000000, 50, 50, false);
        particle_builder->legacy_spawn_sphere(9000, glm::vec3(0, 0, 0), 10000, 10, 10, 0, 0, false);
        break;

    case 26:
        particle_builder->legacy_spawn_globular_cluster(40000, glm::vec3(0.0f), 20000, 10, 10000, 1000000, 10000, 100000, true, false);
        break;

    case 27:
        particle_builder->legacy_spawn_globular_cluster(40000, glm::vec3(0.0f), 200000, 10, 10000, 100000, 1000, 10000, true, false);
        break;

    case 28:
        particle_builder->legacy_spawn_disc(40000, glm::vec3(0.0f), 50000, 1000, 10000, 100000, 200000, 300000, true, false);
        particle_builder->legacy_spawn_globular_cluster(100, glm::vec3(0, 0, 0), 1000, 10, 100000000, 1000000000, 10000, 100000, true, false);
        break;

    case 29:
        particle_builder->legacy_spawn_disc(40000, glm::vec3(0.0f), 50000, 1000, 10000, 100000, 200000, 300000, true, true);
        particle_builder->legacy_spawn_globular_cluster(100, glm::vec3(0, 0, 0), 1000, 10, 100000000, 1000000000, 10000, 100000, true, false);
        break;

    case 30:
        particle_builder->legacy_spawn_disc(40000, glm::vec3(0.0f), 100000, 100, 10000, 100000, 100000, 200000, true, false);
        particle_builder->legacy_spawn_globular_cluster(100, glm::vec3(0.0f), 1000, 10, 100000000, 1000000000, 10000, 100000, true, false);
        break;

    case 31:
        particle_builder->legacy_spawn_disc(30000, glm::vec3(0.0f), 100, 100000, 10000, 100000, 100000, 500000, true, false);
        particle_builder->legacy_spawn_disc(10000, glm::vec3(0.0f), 100000, 10, 10000, 100000, 10000, 100000, true, false);
        particle_builder->legacy_spawn_globular_cluster(100, glm::vec3(0, 0, 0), 1000, 10, 10000000, 100000000, 10000, 100000, true, false);
        break;

    case 32:
        particle_builder->legacy_spawn_disc(20000, glm::vec3(-200000, -1000, 0), 100000, 1000, 10000, 100000, 100000, 200000, true, false);
        particle_builder->legacy_spawn_globular_cluster(100, glm::vec3(-200000, 0, 0), 1000, 10, 100000000, 1000000000, 10000, 100000, true, false);
        particle_builder->legacy_spawn_disc(20000, glm::vec3(200000, 1000, 0), 100000, 1000, 10000, 100000, 100000, 200000, true, false);
        particle_builder->legacy_spawn_globular_cluster(100, glm::vec3(200000, 0, 0), 1000, 10, 100000000, 1000000000, 10000, 100000, true, false);
        break;

    case 33:
        particle_builder->legacy_spawn_disc(10000, glm::vec3(0, -200000, 0), 100, 1000000, 100000000, 100000000, 100000, 500000, true, false);
        particle_builder->legacy_spawn_disc(20000, glm::vec3(0, 0, 0), 100, 1000000, 10000, 100000, 100000, 500000, true, false);
        particle_builder->legacy_spawn_disc(10000, glm::vec3(0, 200000, 0), 100, 1000000, 10000, 100000000, 100000, 500000, true, false);
        break;

    case 34:
        particle_builder->legacy_spawn_globular_cluster(100000, glm::vec3(0.0f), 20000, 10, 10000, 1000000, 10000, 100000, true, false);
        break;

    default:
        break;
    }
}
