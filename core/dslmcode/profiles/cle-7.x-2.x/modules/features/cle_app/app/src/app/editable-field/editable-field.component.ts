import { Component, OnInit, Input, Output, EventEmitter, HostListener, ElementRef } from '@angular/core';
import { FormGroup, FormBuilder } from '@angular/forms';

@Component({
  selector: 'app-editable-field',
  templateUrl: './editable-field.component.html',
  styleUrls: ['./editable-field.component.css']
})
export class EditableFieldComponent implements OnInit {
  @Input() type:string = 'text';
  @Input() content:string = '';
  @Output() contentUpdated:EventEmitter<any> = new EventEmitter();
  editing:boolean = false;
  form: FormGroup;
  
  constructor(
    private el:ElementRef,
    private formBuilder:FormBuilder
  ) { 
    this.form = this.formBuilder.group({
      content: this.content
    })
  }

  ngOnInit() {
    this.form.patchValue({
      content: this.content
    })
  }

  beginEditing() {
    this.editing = true;
  }

  endEditing() {
    this.editing = false;
    setTimeout(() => this.saveNewContent(), 400);
  }

  saveNewContent() {
    this.contentUpdated.emit(this.form.value.content);
  }
}
