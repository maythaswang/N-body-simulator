
#include <GLCommon.h>
#include <Shader.h>
#include <iostream>
#include <vector>

void sample_compute_shader()
{
	Shader comp_shader_program = Shader();
	GLuint compute_shader = comp_shader_program.compile_shader("./shader_source/sample.comp.glsl", GL_COMPUTE_SHADER);
	comp_shader_program.link_shader(compute_shader);

	GLuint tmp_n = 64;
	std::vector<GLfloat> tmp_data(tmp_n);
	std::vector<GLfloat> tmp_data2(tmp_n);
	std::vector<GLfloat> tmp_data3(tmp_n);

	for (int i = 0; i < tmp_n; i++)
	{
		tmp_data[i] = i;
		tmp_data2[i] = 3;
		tmp_data3[i] = 2;
	}

	GLuint SSBO, SSBO2, SSBO3;

	glGenBuffers(1, &SSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, tmp_n * 1 * sizeof(GLfloat), &tmp_data[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO);

	glGenBuffers(1, &SSBO2);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO2);
	glBufferData(GL_SHADER_STORAGE_BUFFER, tmp_n * 1 * sizeof(GLfloat), &tmp_data2[0],GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO2);

	glGenBuffers(1, &SSBO3);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO3);
	glBufferData(GL_SHADER_STORAGE_BUFFER, tmp_n * 1 * sizeof(GLfloat), &tmp_data3[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, SSBO3);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	for (int runs = 0; runs < 10; runs++)
	{

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO); // WHY DO I NEED TO PUT THIS???
		comp_shader_program.use();
		comp_shader_program.set_int("test_num", 1);
		glDispatchCompute(64, 1, 1);
		glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);

		GLfloat *rtn = (GLfloat *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		std::cout << std::endl;
		for (int i = 0; i < tmp_n; i++)
		{
			std::cout << rtn[i] << " ";
		}
		std::cout << std::endl;
	}
	comp_shader_program.delete_shader();
	// glDeleteBuffers(1, &VAO_tmp);
	glDeleteBuffers(1, &SSBO);
	glDeleteBuffers(1, &SSBO2);
	glDeleteBuffers(1, &SSBO3);
}