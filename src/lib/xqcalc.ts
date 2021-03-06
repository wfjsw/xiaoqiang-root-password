import md5 from 'md5'

const snType = {
  '6d2df50a': {
    match: /[0-9]{5}\/[0-9A-Z]{9}/,
    calculator: (sn: string): string => md5(`${sn}6d2df50a-250f-4a30-a5e6-d44fb0960aa0`).slice(0, 8)
  }
}

export function calculateRootPassword(sn: string): string {
  for (const [, exp] of Object.entries(snType)) {
    if (exp.match.test(sn)) return exp.calculator(sn)
  }
  return ''
}
