#ifndef MATHDEFS_HPP
#define MATHDEFS_HPP
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/glut.h>

struct vec3
{
	float x;
	float y;
	float z;

	vec3(float x1, float y1, float z1): x(x1), y(y1), z(z1)
	{}
	vec3():x(0),y(0),z(0)
	{}

	vec3 operator+=(const vec3& other)
	{
		x+=other.x;
		y+=other.y;
		z+=other.z;

		return vec3(x+=other.x, y+=other.y,z+=other.z);
	}
	vec3 operator/=(const float)
	{

	}
	vec3 operator+(const vec3& other) const
	{
		return vec3(x+other.x, y+other.y, z+other.z);
	}
	vec3 operator-(const vec3& other) const
	{
		return vec3(x-other.x, y-other.y, z-other.z);
	}	
	vec3 operator/(const float &denom) const
	{
		return vec3(x/denom, y/denom, z/denom);
	}	
	vec3 operator*(const float mult)
	{
		return vec3(x*mult, y*mult, z*mult);
	}
	bool operator<( const vec3 & n ) const 
	{
		if(x != n.x)
			return x < n.x;
		else if(y != n.y)
			return y < n.y;
		else if(z != n.z)
			return z < n.z;
		return length() < n.length();   
	}
	bool operator==( const vec3 & n ) const 
	{
		return x==n.x&&y==n.y&&z==n.z;   
	}
	float length() const
	{
		return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	}
	void Print() const
	{
		std::cout<<"("<<x<<","<<y<<","<<z<<")"<<std::endl;
	}
};


struct vec4
{
	float x;
	float y;
	float z;
	float w;

	vec4():
	x(0),
	y(0),
	z(0),
	w(0)
	{
	}

	vec4(float x1,float y1,float z1,float w1):
	x(x1),
	y(y1),
	z(z1),
	w(w1)
	{
	}

	vec4& operator+=(const vec4& other)
	{
		x+=other.x;
		y+=other.y;
		z+=other.z;
		w+=other.w;
		return *this;
	}

	vec4& operator-=(const vec4& other)
	{
		x-=other.x;
		y-=other.y;
		z-=other.z;
		w-=other.w;
		return *this;
	}

	vec4 operator/=(const float val)
	{
		x/= val;
		y/= val;
		z/= val;
		w/= val;
		return *this;
	}
	vec4 operator*=(const float val)
	{
		x*= val;
		y*= val;
		z*= val;
		w*= val;
		return *this;
	}
	vec4 operator*=(const vec4& val)
	{
		x*= val.x;
		y*= val.y;
		z*= val.z;
		w*= val.w;
		return *this;
	}
	vec4 operator+(const vec4& other) const
	{	
		vec4 temp = *this;
		temp += other;
		return temp;
	}
	vec4 operator-(const vec4& other) const
	{	
		vec4 temp = *this;
		temp -= other;
		return temp;
	}
	vec4 operator/(const float val) const
	{
		vec4 temp = *this;
		temp /= val;
		return temp;
	}
	vec4 operator*(const float val)
	{
		vec4 temp = *this;
		temp *= val;
		return temp;
	}
	vec4 operator*(const vec4& val)
	{
		vec4 temp = *this;
		temp *= val;
		return temp;
	}
	bool operator<(const vec4& other) const
	{
		if(x != other.x)
			return  x < other.x;
		if(y != other.y)
			return  y < other.y;
		if(z != other.z)
			return  z < other.z;
		if(w != other.w)
			return w < other.w;
		return  x < other.x;
	}

	bool operator!=(const vec4& other) const
	{
		if(x == other.x && y == other.y && z == other.z && w == other.w)
			return false;
		else
			return true;
	}

	friend std::ostream &operator<<(std::ostream& os,const vec4 & obj)
	{
		
		os << obj.x << " " << obj.y << " " << obj.z << " " << obj.w;
		return os;
	}
	GLfloat* toflptr()
	{
		GLfloat arr[4] = {x,y,z,w};
		return arr;
	}
};



struct Triangle
{
	GLuint a;
	GLuint b;
	GLuint c;

	Triangle(GLuint a1, GLuint b1, GLuint c1):a(a1),b(b1),c(c1)
	{}

	bool contains(GLuint cont)
	{
		if(a == cont)
			return true;
		if(b == cont)
			return true;
		if(c == cont)
			return true;
		return false;
	}
};



float getRandom(float max, float min)
{
	return((float(rand()) / float(RAND_MAX)) * (max - (min))) + (min);
}


float getVectorDistance(vec3 a, vec3 b)
{
	return sqrt(pow((a.x-b.x),2) + pow((a.y-b.y),2) + pow((a.z-b.z),2));
}



float dot(vec3 a, vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}



vec3 crossProduct(vec3 v1,vec3 v2)
{
	float x = (v1.y * v2.z) - (v1.z * v2.y);	
	float y = (v1.z * v2.x) - (v1.x * v2.z);	
	float z = (v1.x * v2.y) - (v1.y * v2.x);

	return vec3(x,y,z);
}

vec3 normalize(const vec3 p)
{
	vec3 out;
    float magnitude = abs((float)sqrt(p.x * p.x + p.y * p.y + p.z * p.z));
	if (magnitude == 0.0)
        magnitude = 0.000001;

    out = p/magnitude;
	return out;
}


vec3 getMidpoint(const vec3& a, const vec3& b)
{
	const float SCALE = 0.09;

	static std::map<std::pair<vec3,vec3>,vec3> memo;
	

	auto foundResult = memo.find(std::make_pair(a,b));
	if (foundResult!=memo.end()) 
	{
		return foundResult->second;
	}

	auto result = (a+b)/2;
	auto variance = SCALE * getVectorDistance(a,b);
	
	result = vec3(getRandom(result.x + variance, result.x - variance)
		,getRandom(result.y + variance, result.y - variance)
		,getRandom(result.z + variance, result.z - variance));

	memo.insert(std::make_pair(std::make_pair(a,b),result));
	memo.insert(std::make_pair(std::make_pair(b,a),result));
	return result;

}


vec3 getCross(const vec3&a, const vec3&b)
{
	vec3 outVec;
	outVec.x = (float)(a.y * b.z) - (float)(b.y * a.z);
	outVec.y = (float)(a.z * b.x) - (float)(b.z * a.x);
	outVec.z = (float)(a.x * b.y) - (float)(b.x * a.y);

	return outVec;


}

double findnoise2(double x,double y)
{
	int n=(int)x+(int)y*57;
	n=(n<<13)^n;
	int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
	return 1.0-((double)nn/1073741824.0);
}

double interpolate1(double a,double b,double x)
{
	double ft=x * 3.1415927;
	double f=(1.0-cos(ft))* 0.5;
	return a*(1.0-f)+b*f;
}


double noise(double x,double y)
{
 double floorx=(double)((int)x);//This is kinda a cheap way to floor a double integer.
 double floory=(double)((int)y);
 double s,t,u,v;//Integer declaration
 s=findnoise2(floorx,floory); 
 t=findnoise2(floorx+1,floory);
 u=findnoise2(floorx,floory+1);//Get the surrounding pixels to calculate the transition.
 v=findnoise2(floorx+1,floory+1);
 double int1=interpolate1(s,t,x-floorx);//Interpolate between the values.
 double int2=interpolate1(u,v,x-floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
 return interpolate1(int1,int2,y-floory);//Here we use y-floory, to get the 2nd dimension.
}





float getVectorLength(glm::vec3 vec)
{

	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));

}


float myGetVectorLength(vec3 vec)
{

	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));

}


float getAngle(vec3 a, vec3 b)
{
	return acosf((dot(a,b)) / (myGetVectorLength(a) * myGetVectorLength(b)));

}


glm::vec3 getUnitVector(glm::vec3 vec)
{
	glm::vec3 returnVec;

	returnVec.x = vec.x / getVectorLength(vec);
	returnVec.y = vec.y / getVectorLength(vec);
	returnVec.z = vec.z / getVectorLength(vec);


	return returnVec;
}

vec3 myGetUnitVector(vec3 vec)
{
	vec3 returnVec;

	returnVec.x = vec.x / myGetVectorLength(vec);
	returnVec.y = vec.y / myGetVectorLength(vec);
	returnVec.z = vec.z / myGetVectorLength(vec);


	return returnVec;

}







#endif
