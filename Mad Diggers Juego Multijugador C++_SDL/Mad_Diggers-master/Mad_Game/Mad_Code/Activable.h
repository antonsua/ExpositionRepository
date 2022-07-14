//Mad_Diggers

#ifndef ACTIVABLE_H_
#define ACTIVABLE_H_

class Activable
{
public:
	Activable();
	virtual ~Activable();

	bool isActive() const;
	void setActive(bool active);
	bool toggleActive();

private:
	bool active_;   // indicates if the object is active
};

#endif /* ACTIVABLE_H_ */
