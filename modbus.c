#include "m_pd.h"
#include <modbus/modbus.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <modbus/modbus-rtu.h>
#include <modbus/modbus-version.h>

static t_class *modbus_class;


// Modbus class:
typedef struct _modbus {
  t_object  x_obj;
  char s_device[128];
  int i_baudrate;
  int i_device_id;
  modbus_t* t_modbus_handle;
  int connected;
  t_outlet* f_out;
} t_modbus;

void modbus_bang(t_modbus *x)
{
}

void *modbus_new(t_symbol *s, int argc, t_atom *argv)
{
  t_modbus *x = (t_modbus *)pd_new(modbus_class);
  x->f_out = outlet_new(&x->x_obj, &s_float);
  if(argc == 3)
  {
    atom_string(argv, x->s_device, 128);
    //strcpy(x->s_device, (char*)argv);
    x->i_baudrate = *((int*)(argv + 1));
    x->i_device_id = *((int*)(argv + 2));
    //x->t_modbus_handle = modbus_new_rtu(x->s_device, x->i_baudrate, 'N', 8, 1);
  }

  return (void *)x;
}

void read_register(t_modbus *x, t_symbol* address)
{
  uint16_t value = 0;
  post("Read address: %s", address->s_name);
  int i_address = (int)strtol(address->s_name, NULL, 0);

  if(x->t_modbus_handle != NULL && x->connected) 
  {
    // Convert the freq into uint16:
    int ret = modbus_read_registers(x->t_modbus_handle, i_address, 1, &value);
    if(ret == -1)
    {
      post("Could not read register %x!", i_address);
    }
    outlet_float(x->f_out, value);
  }
  else
  {
    post("Modbus not connected!");
  }
}

void write_register(t_modbus *x, t_symbol* address, float value)
{
  post("Write address: %s", address->s_name);
  int i_address = (int)strtol(address->s_name, NULL, 0);

  if(x->t_modbus_handle != NULL && x->connected) 
  {
    // Convert the freq into uint16:
    int ret = modbus_write_register(x->t_modbus_handle, i_address, (uint16_t)value);
    if(ret == -1)
    {
      post("Could not write register %x! val: %f", i_address, value);
    }
  }
  else
  {
    post("Modbus not connected!");
  }
}

void modbus_do_connect(t_modbus *x)
{
    x->t_modbus_handle = modbus_new_rtu(x->s_device, x->i_baudrate, 'N', 8, 1);
    if(x->t_modbus_handle == NULL)
    {
      post("Could not create modbus handle");
    }
    modbus_rtu_set_serial_mode(x->t_modbus_handle, MODBUS_RTU_RS232);
    modbus_set_slave(x->t_modbus_handle, x->i_device_id);
    if(modbus_connect(x->t_modbus_handle) == -1)
    {
      post("Could not connect modbus on: %s!", x->s_device);
      modbus_free(x->t_modbus_handle);
      x->connected = 0;
    }
    else
    {
      post("Modbus connected");
      x->connected = 1;
    }
}

void modbus_setup(void) {
  modbus_class = class_new(gensym("modbus"),
        (t_newmethod)modbus_new,
        0, sizeof(t_modbus),
        CLASS_DEFAULT,
        A_GIMME, 0);

  class_addbang(modbus_class, modbus_bang);

  class_addmethod(modbus_class,
      (t_method)modbus_do_connect,
      gensym("connect"), 0);
  class_addmethod(modbus_class,
      (t_method)write_register,
      gensym("write_register"), A_DEFSYMBOL, A_FLOAT, 0);
  class_addmethod(modbus_class,
      (t_method)read_register,
      gensym("read_register"), A_DEFSYMBOL, 0);
  class_sethelpsymbol(modbus_class, gensym("help-modbus"));
}
