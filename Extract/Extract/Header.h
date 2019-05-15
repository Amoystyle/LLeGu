#ifndef HEADER_H_
#define HEADER_H_

#include <stdint.h>
#include <elf.h>

#pragma pack(push)
#pragma pack(1)

struct SectionTable {
  ElfW(Off)  shoff;
  ElfW(Half) shnum;
  ElfW(Half) shentsize;
  ElfW(Half) shstrndx;
  ElfW(Addr) mapping_base_;

  bool section_table_get_strtab_section(ElfW(Shdr) &strtab);
  bool section_table_get_symtab_section(ElfW(Shdr) &symtab);
  bool section_table_get_hash_section(ElfW(Shdr)   &hash);
};

// sizeof = 0x58
struct Header {
  ElfW(Addr)    min_vaddr;            // +00: ��С�����ַ ϣ���ڴ汻�ֲ��ĵ�ַ
  size_t        load_size_;           // +04: ���пɼ��ض�
  size_t        load_seg_num_;        // +0A: �ɼ��ضε�����
  ElfW(Addr)    ARM_exidx;            // +50: -A8 v56
  size_t        ARM_exidx_count;      // +54: -A4 v57
  uint32_t      nbucket_;             // +34: bucket_ ������
  uint32_t      nchain_;              // +38: chanin_ ������
  ElfW(Addr)    bucket_;              // +3C: Hash ���ƫ�ƣ�ÿһ��4�ֽ�, load_size_=Header.nbucket_ * 4
  ElfW(Addr)    strtab_;              // +10: .dynstr, load_size_=Header.bucket_ - Header.strtab_ - 8; ��Ϊ�ַ������������bucket
  ElfW(Addr)    symtab_;              // +14: .dynsym, load_size_=Header.nchain_ * 0x10; nchain_ ��ʾ���ű�ĸ���
  ElfW(Addr)    plt_rel_;             // +40: DT_JMPREL .rel.plt��ƫ��
  ElfW(Addr)    rel_;                 // +4C: DT_REL .rel.dyn��ƫ��

  size_t   strtab_size_;
  size_t   plt_rel_count_;       // +44: DT_PLTRELSZ .rel.plt��������ÿһ��8�ֽ�
  size_t   rel_count_;           // +48: DT_RELSZ .rel.dyn��������ÿһ��8�ֽ�
  size_t   init_array_count_;    // +2A: ��Ϊû��ʹ�ã�����һ���²�
  size_t   fini_array_count_;    // +28: ��Ϊû��ʹ�ã�����һ���²�

  ElfW(Addr)    init_func_;           // +18: ��ʼ��������ƫ��
  ElfW(Addr)    fini_func_;           // +20: ��Ϊû��ʹ�ã�����һ���²�

  ElfW(Addr)    init_array_;          // +1C: ��ʼ�����������ƫ��
  ElfW(Addr)    fini_array_;          // +24: ��Ϊû��ʹ�ã�����һ���²�

  size_t        needed_count_;        // +2C: ��ִ�н�ѹ����ǰ����Ҫ���ض��ٸ�������lib
  ElfW(Addr)    needed_strtab_;       // +30: ָ������Ҫ�����ص�library�ַ������ƫ��
};

// sizeof = 0x18
struct Loadable {
  ElfW(Addr) p_vaddr;               // +00:
  ElfW(Addr) p_memsz;               // +04:
  ElfW(Off)  p_offset;              // +08: ���ݾ��� Header ��ƫ��
  ElfW(Addr) p_filesz;              // +0C: �������ļ���ռ�õ�ʵ�ʴ�С
  ElfW(Word) p_flags;               // +10: ��ʶ�˶���д��ִ��
  uint8_t*   data;
};


struct Header_ {
  ElfW(Addr)    min_vaddr;            // +00: ��С�����ַ ϣ���ڴ汻�ֲ��ĵ�ַ
  size_t        self_size_;
  size_t        load_size_;           // +04: ���пɼ��ض�
  size_t        load_seg_num_;        // +0A: �ɼ��ضε�����
  ElfW(Addr)    ARM_exidx;            // +50: -A8 v56
  size_t        ARM_exidx_count;      // +54: -A4 v57
  ElfW(Addr)    bucket_;              // +3C: Hash ���ƫ�ƣ�ÿһ��4�ֽ�, load_size_=Header.nbucket_ * 4
  ElfW(Addr)    strtab_;              // +10: .dynstr, load_size_=Header.bucket_ - Header.strtab_ - 8; ��Ϊ�ַ������������bucket
  ElfW(Addr)    symtab_;              // +14: .dynsym, load_size_=Header.nchain_ * 0x10; nchain_ ��ʾ���ű�ĸ���
  ElfW(Addr)    plt_rel_;             // +40: DT_JMPREL .rel.plt��ƫ��
  ElfW(Addr)    rel_;                 // +4C: DT_REL .rel.dyn��ƫ��

#ifdef __LP64__
  Elf64_Xword   plt_rel_count_;
  Elf64_Xword   rel_count_;
  Elf64_Xword   init_array_count_;    // +2A: ��Ϊû��ʹ�ã�����һ���²�
  Elf64_Xword   fini_array_count_;    // +28: ��Ϊû��ʹ�ã�����һ���²�
#else
  Elf32_Sword   plt_rel_count_;       // +44: DT_PLTRELSZ .rel.plt��������ÿһ��8�ֽ�
  Elf32_Sword   rel_count_;           // +48: DT_RELSZ .rel.dyn��������ÿһ��8�ֽ�
  Elf32_Sword   init_array_count_;    // +2A: ��Ϊû��ʹ�ã�����һ���²�
  Elf32_Sword   fini_array_count_;    // +28: ��Ϊû��ʹ�ã�����һ���²�
#endif

  ElfW(Addr)    init_func_;           // +18: ��ʼ��������ƫ��
  ElfW(Addr)    fini_func_;           // +20: ��Ϊû��ʹ�ã�����һ���²�

  ElfW(Addr)    init_array_;          // +1C: ��ʼ�����������ƫ��
  ElfW(Addr)    fini_array_;          // +24: ��Ϊû��ʹ�ã�����һ���²�

  size_t        needed_count_;        // +2C: ��ִ�н�ѹ����ǰ����Ҫ���ض��ٸ�������lib
  ElfW(Addr)    needed_strtab_;       // +30: ָ������Ҫ�����ص�library�ַ������ƫ��
};


#pragma pack(pop)

#endif