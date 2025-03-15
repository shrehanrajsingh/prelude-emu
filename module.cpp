#include "module.hpp"

namespace pl
{
void
swap (Module &first, Module &second) noexcept
{
  std::swap (first.program, second.program);
}

Module &
Module::operator= (Module &rhs)
{
  Module temp (rhs);
  swap (*this, temp);
  return *this;
}

Module &
Module::operator= (Module &&rhs)
{
  swap (program, rhs.program);
  return *this;
}

void
Module::add_register (char *_Name, RegisterType _Type)
{
  Register *nr = nullptr;

  switch (_Type)
    {
    case REG_TYPE_8:
      {
        Register8 *n8 = new Register8 (0);
        nr = n8;
      }
      break;

    case REG_TYPE_16:
      {
        Register16 *n16 = new Register16 (0);
        nr = n16;
      }
      break;

    default:
      throw "invalid_register_type";
      break;
    }

  nr->set_name (_Name);
  nr->set_id (regmap.size ());

  regmap.push_back (nr);
}

Register *
Module::get_register (char *_Name)
{
  for (Register *r : regmap)
    if (!strcmp (r->get_name (), _Name))
      return r;

  return nullptr;
}

void
Module::exec ()
{
  int i;

  Register8 *A = static_cast<Register8 *> (get_register ("A"));
  Register8 *B = static_cast<Register8 *> (get_register ("B"));
  Register8 *C = static_cast<Register8 *> (get_register ("C"));
  Register8 *D = static_cast<Register8 *> (get_register ("D"));
  Register8 *E = static_cast<Register8 *> (get_register ("E"));
  Register8 *F = static_cast<Register8 *> (get_register ("F"));

  Register8 *SF = static_cast<Register8 *> (get_register ("SF"));

  while ((i = fetch ()) != HALT)
    {
      switch (i)
        {
        case MOV:
          {
            int regid = fetch ();
            int val = fetch ();

            add_to_register (regid, val);
          }
          break;
        case ADD:
          {
            int a = st.pop (), b = st.pop ();
            st.push (a + b);
          }
          break;
        case PUSH_v:
          {
            st.push (fetch ());
          }
          break;
        case POP:
          {
            DEBUG (std::cout << st.pop ());
          }
          break;
        case SYSCALL:
          {
            switch (A->get_val ())
              {
              case 1:
                {
                  /* standard file operations */
                  switch (B->get_val ())
                    {
                    case FSTREAM_STDOUT:
                      {
                        /*
                          `C` -> message length
                          `D` -> message offset in data segment
                        */

                        const char vc_val = C->get_val ();
                        char i = 0;

                        while (i < vc_val)
                          {
                            putchar (data[i]);
                            i++;
                          }
                      }
                      break;

                    default:
                      break;
                    }
                }
                break;

              default:
                break;
              }
          }
          break;
        case CMP_rv:
          {
            Register8 *r = static_cast<Register8 *> (regmap[fetch ()]);
            char v = fetch ();
            char res = r->get_val () - v;

            char &sfv = SF->get_val ();
            sfv = 0;

            if (!res)
              {
                /* ZF = 1 */
                sfv |= (StatusFlagBits::SF_ZF);
              }
            else if (res < 0)
              {
                /* SF != OF */
                sfv |= (StatusFlagBits::SF_SF);
              }
            else
              {
                /* SF == OF */
              }
          }
          break;

        case SJE:
          {
            short pc_pres = get_pc ();

            char n = fetch ();
            const char sfv = SF->get_val ();

            if ((sfv & StatusFlagBits::SF_ZF) != 0)
              {
                if (n > 0)
                  {
                    /*
                      the next loop will also call fetch()
                      so we need to jump to (n - 1)
                      and the one jump will be made in the next
                      cycle of while loop while fetching instruction
                    */
                    // while ((n--) > 1)
                    //   fetch ();
                    pc_pres += n;
                  }
                else
                  pc_pres += (n - 1);

                set_pc (pc_pres);
              }
          }
          break;

        case JE:
          {
            short pc_pres = get_pc ();

            short n1 = static_cast<short> (fetch ());
            short n2 = static_cast<short> (fetch ());

            short n;

            if (PL_ARCH == ARCH_LITTLE_ENDIAN)
              n = n1 | (n2 << 8);
            else
              n = (n1 << 8) | n2;

            const char sfv = SF->get_val ();

            if ((sfv & StatusFlagBits::SF_ZF) != 0)
              {
                if (n > 0)
                  {
                    // while ((n--) > 1)
                    //   fetch ();
                    pc_pres += (n + 1);
                  }
                else
                  {
                    // DEBUG (std::cout << "JE does not support negative jumps.
                    //                     "
                    //                     "Implement it.");
                    pc_pres += (n - 1);
                  }

                set_pc (pc_pres);
              }
          }
          break;

        default:
          DEBUG (std::cout << "Invalid instruction: " << i << '\n');
          throw "invalid_instruction";
          break;
        }
    }
}

void
Module::add_to_register (int regid, int val)
{
  /*
    Register ID is same as the index it appears
    in regmap
  */
  if (regid < 0 || regid >= regmap.size ())
    throw "regid_out_of_bounds";

  regmap[regid]->set_val (val);
}
} // namespace pl
