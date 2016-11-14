import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { FormGroup, FormBuilder } from '@angular/forms';
import { Critique } from '../../critique';
import { CritiqueService } from '../../critique.service';
import { Submission } from '../../submission';

@Component({
  selector: 'cle-critique-form',
  templateUrl: './critique-form.component.html',
  styleUrls: ['./critique-form.component.css'],
  providers: [CritiqueService]
})
export class CritiqueFormComponent implements OnInit {
  @Input()
  submission;

  @Output()
  critiqueCreated: EventEmitter<any> = new EventEmitter();

  form: FormGroup;

  constructor(
    private fb: FormBuilder,
    private critiqueService: CritiqueService
  ) { 
    this.form = this.fb.group({
      body: ''
    });
  }

  ngOnInit() {
  }

  submitForm() {
    // save new critique
    if (this.form.value) {
      let newCritique: Critique =  new Critique(this.form.value.body);
      newCritique.submissionId = this.submission.nid;
      this.critiqueService.createCritique(newCritique)
        .subscribe(res => {
          if (res.ok) {
            this.form.reset();
            this.critiqueCreated.emit(res.json());
          }
        });
    }
    // update existing critique
    else {
    }
  }
}
